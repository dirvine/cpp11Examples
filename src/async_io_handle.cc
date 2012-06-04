#include <future>
#include <iostream>
#include <vector>
#include <streambuf>
#include <fstream>
#include <atomic>

#include <queue>
#include <mutex>
#include <condition_variable>

// thread and exception safe queue
// pop elements by reference to not throw :)

template<typename T>
class SafeQueue {
public:
  SafeQueue() :
    queue_(),
    mutex_(),
    condition_() {};
    // move OK copy disallowed
  SafeQueue(const SafeQueue&& other) {
    other.queue_(std::move(queue_));
    other.condition_(std::move(condition_));
    other.mutex_(std::move(mutex_));
  }
  SafeQueue& operator=(const SafeQueue&& other) {
    other.queue_ = (std::move(queue_));
    other.condition_ = (std::move(condition_));
    other.mutex_ = (std::move(mutex_));
  }
  bool Empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
  }
  unsigned Size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
  }
  void Push(T element){
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(element);
    condition_.notify_one();
  }
  bool TryPop(T &element) {
    std::lock_guard<std::mutex> lock(mutex_);
    if(queue_.empty()){
      return false;
    }
    element = queue_.front();
    queue_.pop();
    return true;
  }
  void WaitAndPop(T &element) {
    std::unique_lock<std::mutex> lock(mutex_);
    while(queue_.empty()) {
      condition_.wait(lock);  // needs unique_lock
    }
    element = queue_.front();
    queue_.pop();
  }

private:
  SafeQueue& operator=(const SafeQueue&);
  SafeQueue(const SafeQueue& other);
  std::queue<T> queue_;
  mutable std::mutex mutex_;
  std::condition_variable condition_;
};


class aio {
    class io_request
    {
        std::streambuf* is;
        unsigned read_count;
        std::promise<std::vector<char> > p;
    public:
        explicit io_request(std::streambuf& is_,unsigned count_):
            is(&is_),read_count(count_)
        {}

        io_request(io_request&& other):
            is(other.is),
            read_count(other.read_count),
            p(std::move(other.p))
        {}

        io_request():
            is(0),read_count(0)
        {}

        std::future<std::vector<char> > get_future()
        {
            return p.get_future();
        }

        void process()
        {
            try
            {
                std::vector<char> buffer(read_count);

                unsigned amount_read=0;
                while((amount_read != read_count) &&
                      (is->sgetc()!=std::char_traits<char>::eof()))
                {
                    amount_read+=is->sgetn(&buffer[amount_read],read_count-amount_read);
                }

                buffer.resize(amount_read);

                p.set_value(std::move(buffer));
            }
            catch(...)
            {
                p.set_exception(std::current_exception());
            }
        }
    };

    SafeQueue<io_request> request_queue;
    std::atomic<bool> done;

    void io_thread()
    {
        while(!done)
        {
            io_request req;
            request_queue.WaitAndPop(req);
            req.process();
        }
    }

    std::thread iot;

public:
    aio():
        done(false),
        iot(&aio::io_thread,this)
    {}

    std::future<std::vector<char> > queue_read(std::streambuf& is,unsigned count)
    {
        io_request req(is,count);
        std::future<std::vector<char> > f(req.get_future());
        request_queue.Push(std::move(req));
        return f;
    }

    ~aio()
    {
        done=true;
        request_queue.Push(io_request());
        iot.join();
    }
};

void do_stuff()
{}

void process_data(std::vector<char> v)
{
    for(unsigned i=0;i<v.size();++i)
    {
        std::cout<<v[i];
    }
    std::cout<<std::endl;
}

int main()
{
    aio async_io;

    std::filebuf f;
    f.open("my_file.dat",std::ios::in | std::ios::binary);

    std::future<std::vector<char> > fv=async_io.queue_read(f,1048576);

    do_stuff();
    process_data(fv.get());

    return 0;
}
