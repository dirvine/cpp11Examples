#include <iostream>
enum class ConnectType : int32_t {
    kSingle = 100,
    kClosest,
    kGroup
};

int main()
{
    std::cout << static_cast<int32_t>(ConnectType::kSingle) << std::endl;
    std::cout << static_cast<int32_t>(ConnectType::kGroup) << std::endl;
    return 0;
}

