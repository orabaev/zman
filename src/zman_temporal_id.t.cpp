#include "catch/catch.hpp"
#include "zman_temporal_id.hpp"
#include <type_traits>

using namespace zman;

TEST_CASE("invalid_id")
{
    REQUIRE( invalid_id<int>::value == 0 );
}

TEST_CASE("is_valid_id")
{
    REQUIRE( is_valid_id( 0) == false );
    REQUIRE( is_valid_id( 1) == true  );
    REQUIRE( is_valid_id(-1) == true  );
}

TEST_CASE("temporal_id.defaults")
{
    using temporal_id_type = temporal_id<int,int>;
    static_assert( std::is_default_constructible<temporal_id_type>::value );
    static_assert( std::is_copy_constructible<temporal_id_type>::value    );
    static_assert( std::is_move_constructible<temporal_id_type>::value    );
    static_assert( std::is_move_constructible<temporal_id_type>::value    );
}

TEST_CASE("temporal_id.id")
{
    using temporal_id_type = temporal_id<int,int>;

    temporal_id_type tid(12, 7);
    REQUIRE( tid.id() == 12 );
}

TEST_CASE("temporal_id.time_point")
{
    using temporal_id_type = temporal_id<int,int>;

    temporal_id_type tid(13, 11);
    REQUIRE( tid.time_point() == 11);
}

TEST_CASE("temporal_id.comparison")
{
    using temporal_id_type = temporal_id<int,int>;

    temporal_id_type tid1(3, 11);
    temporal_id_type tid2(2, 11);
    temporal_id_type tid3(1, 13);

    REQUIRE ( tid1 == tid2 );
    REQUIRE ( tid1 != tid3 );
    REQUIRE ( tid1 <  tid3 );
    REQUIRE ( tid1 <= tid3 );
    REQUIRE ( tid1 <= tid2 );
    REQUIRE ( tid3 >  tid1 );
    REQUIRE ( tid3 >= tid1 );
    REQUIRE ( tid1 >= tid2 );
}

