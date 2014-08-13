
#define CATCH_CONFIG_MAIN 
#include <future>
#include <iostream>
#include <sstream>
#include <vector>
#include "catch.hpp"

TEST_CASE("task manager", "[task]") {
  //    std::cout << "Main thread id: " << std::this_thread::get_id()
  //        << std::endl;
  auto func = [&]
    {
       std::this_thread::sleep_for(std::chrono::seconds(1));
       std::ostringstream oss;
       oss << std::this_thread::get_id();
       std::string output(oss.str());
       // printf(" thread %s \n", output.c_str());
    };

  std::vector<std::future<void> > vec;

  for (int i = 0; i < 200; ++i) {
    vec.push_back(std::async(std::launch::async, func));
  }

  std::this_thread::sleep_for(std::chrono::seconds(3));
  for(auto &j  : vec) {
    j.get();
  }

}
