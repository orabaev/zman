#include "catch/catch.hpp"
#include "zman_test_util.t.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

using time_point_type = int;
using key_type        = string;
using value_type      = int;
using tu = test_util<time_point_type, key_type, value_type>;

TEST_CASE("test_util.value")
{
    CHECK( 1 == tu::value(1) );
}

TEST_CASE("test_util.temporal_value")
{
    auto value = tu::temporal_value({{1,7},{2,8},{4, std::nullopt}});

    CHECK( nullptr ==  value.find(0) );
    CHECK( 7       == *value.find(1) );
    CHECK( 8       == *value.find(2) );
    CHECK( 8       == *value.find(3) );
    CHECK( nullptr ==  value.find(4) );
}

TEST_CASE("test_util.array")
{
    tu::array_type array{1,2,3};
    CHECK( array == tu::array({1,2,3}) );
}
