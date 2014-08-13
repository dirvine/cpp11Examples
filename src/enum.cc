#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

enum class ConnectType : int32_t {
    kSingle = 100,
    kClosest,
    kGroup
};

TEST_CASE("Static ENUM cast", "[enum]") {
    CHECK(100 == static_cast<int32_t>(ConnectType::kSingle));
    CHECK(102 == static_cast<int32_t>(ConnectType::kGroup));
}

