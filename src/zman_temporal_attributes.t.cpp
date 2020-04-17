#include "catch/catch.hpp"
#include "zman_temporal_attributes.hpp"
#include "zman_temporal_data.hpp"
#include "zman_time_line.hpp"
#include <type_traits>

using namespace zman;

TEST_CASE("temporal_attributes.defaults")
{
    using temporal_data_type       = temporal_data<int,int>;
    using time_line_type           = time_line<temporal_data_type>;
    using temporal_attributes_type = temporal_attributes<time_line_type, int>;

    static_assert( std::is_default_constructible<temporal_attributes_type>::value );
    static_assert( std::is_copy_constructible<temporal_attributes_type>::value    );
    static_assert( std::is_move_constructible<temporal_attributes_type>::value    );
    static_assert( std::is_move_constructible<temporal_attributes_type>::value    );
}

