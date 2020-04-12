#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "zman_time_line.hpp"
#include <type_traits>

using namespace zman;

TEST_CASE("time_line", "[default]")
{
    static_assert( std::is_default_constructible<time_line<int>>::value );
    static_assert( std::is_move_constructible<time_line<int>>::value );
}
