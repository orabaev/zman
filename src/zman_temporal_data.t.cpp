#include "catch/catch.hpp"
#include "zman_temporal_data.hpp"
#include <type_traits>

using namespace zman;

TEST_CASE("temporal_data.defaults")
{
    using temporal_data_type = temporal_data<int,int>;
    static_assert( std::is_default_constructible<temporal_data_type>::value );
    static_assert( std::is_copy_constructible<temporal_data_type>::value    );
    static_assert( std::is_move_constructible<temporal_data_type>::value    );
    static_assert( std::is_move_constructible<temporal_data_type>::value    );
}

TEST_CASE("temporal_data.data")
{
    using temporal_data_type = temporal_data<int,int>;

    temporal_data_type tdata(12, 7);
    CHECK( tdata.data() == 12 );
}

TEST_CASE("temporal_data.time_point")
{
    using temporal_data_type = temporal_data<int,int>;

    temporal_data_type tdata(13, 11);
    CHECK( tdata.time_point() == 11);
}

TEST_CASE("temporal_data.comparison")
{
    using temporal_data_type = temporal_data<int,int>;

    temporal_data_type tdata1(3, 11);
    temporal_data_type tdata2(2, 11);
    temporal_data_type tdata3(1, 13);

    CHECK ( tdata1 == tdata2 );
    CHECK ( tdata1 != tdata3 );
    CHECK ( tdata1 <  tdata3 );
    CHECK ( tdata1 <= tdata3 );
    CHECK ( tdata1 <= tdata2 );
    CHECK ( tdata3 >  tdata1 );
    CHECK ( tdata3 >= tdata1 );
    CHECK ( tdata1 >= tdata2 );
}
