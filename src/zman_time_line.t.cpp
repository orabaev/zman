#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "zman_time_line.hpp"
#include "zman_temporal_id.hpp"
#include <type_traits>

using namespace zman;

TEST_CASE("time_line.defaults")
{
    using temporal_id_type = temporal_id<int,int>;
    static_assert( std::is_default_constructible<time_line<temporal_id_type>>::value );
    static_assert( std::is_move_constructible<time_line<temporal_id_type>>::value );
}
