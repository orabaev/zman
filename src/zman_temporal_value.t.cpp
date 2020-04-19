#include "catch/catch.hpp"
#include "zman_temporal_value.hpp"
#include <optional>
#include <type_traits>

using namespace zman;
using namespace std;

TEST_CASE("temporal_value.defaults")
{
    using temporal_value_type = temporal_value<int,string>;
    static_assert( std::is_default_constructible<temporal_value_type>::value );
    static_assert( std::is_copy_constructible<temporal_value_type>::value    );
    static_assert( std::is_move_constructible<temporal_value_type>::value    );
    static_assert( std::is_move_assignable<temporal_value_type>::value       );
}

TEST_CASE("temporal_value.value")
{
    using temporal_value_type = temporal_value<int,string>;

    temporal_value_type tvalue(12, "value");
    CHECK( tvalue.value() == "value" );
}

TEST_CASE("temporal_value.optional_value")
{
    using value_type          = optional<string>;
    using temporal_value_type = temporal_value<int,value_type>;

    SECTION("value")
    {
        string str = "value";
        temporal_value_type tvalue(12, str);
        CHECK( tvalue.value().value() == "value" );
    }

    SECTION("empty")
    {
        temporal_value_type tvalue(12, value_type{});
        CHECK( tvalue.value().value_or("empty") == "empty" );
    }
}

TEST_CASE("temporal_value.time_point")
{
    using temporal_value_type = temporal_value<int,string>;

    temporal_value_type tvalue(11, "value");
    CHECK( tvalue.time_point() == 11);
}

TEST_CASE("temporal_value.comparison")
{
    using temporal_value_type = temporal_value<int,string>;

    temporal_value_type tvalue1(11, "C");
    temporal_value_type tvalue2(11, "B");
    temporal_value_type tvalue3(13, "A");

    CHECK ( tvalue1 == tvalue2 );
    CHECK ( tvalue1 != tvalue3 );
    CHECK ( tvalue1 <  tvalue3 );
    CHECK ( tvalue1 <= tvalue3 );
    CHECK ( tvalue1 <= tvalue2 );
    CHECK ( tvalue3 >  tvalue1 );
    CHECK ( tvalue3 >= tvalue1 );
    CHECK ( tvalue1 >= tvalue2 );
}
