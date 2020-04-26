#include "catch/catch.hpp"
#include "zman_temporal_convert.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

using time_point_type = int;
using key_type        = string;
using value_type      = int;
using convert         = temporal_convert<time_point_type, key_type, value_type>;
using attribute_t     = typename convert::attribute; 

TEST_CASE("temporal_convert.to_non_temporal_type.value")
{
    attribute_t::timepoint_type timepoint = 1;
    value_type                  value     = 12;
    auto optional_value = convert::to_non_temporal_type(timepoint, value);
    CHECK( *optional_value == value );
}

TEST_CASE("temporal_convert.to_non_temporal_type.array")
{
    attribute_t::timepoint_type timepoint = 1;
    attribute_t::array_type     array{1,2,3};
    auto optional_value = convert::to_non_temporal_type(timepoint, array);
    CHECK( *optional_value == array );
}

TEST_CASE("temporal_convert.to_non_temporal_type.temporal_value")
{
    attribute_t::temporal_value_type temporal_value;    

    attribute_t::timepoint_type timepoint = 1;
    attribute_t::value_type     value     = 10;
    temporal_value.insert(timepoint, value);

    timepoint = 3;
    temporal_value.insert(timepoint);
    
    timepoint = 1;
    auto optional_value = convert::to_non_temporal_type(timepoint, temporal_value);
    CHECK( *optional_value == 10 ); 

    timepoint = 2;
    optional_value = convert::to_non_temporal_type(timepoint, temporal_value);
    CHECK( *optional_value == 10 ); 

    timepoint = 3;
    optional_value = convert::to_non_temporal_type(timepoint, temporal_value);
    CHECK_FALSE( optional_value ); 
}

TEST_CASE("temporal_convert.to_non_temporal_type.temporal_array")
{
    attribute_t::temporal_array_type temporal_array;    
    attribute_t::temporal_value_type temporal_value;

    attribute_t::timepoint_type timepoint;
    { 
        timepoint = 1;
        attribute_t::value_type     value     = 10;
        temporal_value.insert(timepoint, value);
        timepoint = 3;
        temporal_value.insert(timepoint);
        temporal_array.push_back(std::move(temporal_value));
    }

    { 
        timepoint = 2;
        attribute_t::value_type     value     = 55;
        temporal_value.insert(timepoint, value);
        timepoint = 4;
        temporal_value.insert(timepoint);
        temporal_array.push_back(std::move(temporal_value));
    }
    
    timepoint = 1;
    auto optional_value = convert::to_non_temporal_type(timepoint, temporal_array);
    CHECK( (*optional_value).size() ==  1 ); 
    CHECK( (*optional_value)[0]     == 10 ); 

    timepoint = 2;
    optional_value = convert::to_non_temporal_type(timepoint, temporal_array);
    CHECK( (*optional_value).size() ==  2 ); 
    CHECK( (*optional_value)[0]     == 10 );
    CHECK( (*optional_value)[1]     == 55 );

    timepoint = 3;
    optional_value = convert::to_non_temporal_type(timepoint, temporal_array);
    CHECK( (*optional_value).size() ==  1 ); 
    CHECK( (*optional_value)[0]     == 55 );

    timepoint = 4;
    optional_value = convert::to_non_temporal_type(timepoint, temporal_array);
    CHECK_FALSE( optional_value ); 
}

TEST_CASE("temporal_convert.to_non_temporal_type.attribute")
{
    attribute_t::timepoint_type timepoint = 1;

    SECTION("value_type")
    {
        attribute_t::type value(12);
        auto optional_value = convert::to_non_temporal_type(timepoint, value);
        CHECK( *optional_value == value );
    }

    SECTION("array_type")
    {
        attribute_t::array_type  array{1,2,3};
        attribute_t::type        value(array);
        auto optional_value = convert::to_non_temporal_type(timepoint, value);
        CHECK( *optional_value == value );
    }
}

TEST_CASE("temporal_convert.to_non_temporal_type.temporal_attribute")
{
    attribute_t::timepoint_type timepoint = 1;
    attribute_t::timepoint_type invalid_timepoint = 0;

    SECTION("value_type")
    {
        attribute_t::temporal_type  value(12);
        attribute_t::type           expected(12);
        auto optional_value = convert::to_non_temporal_type(timepoint, value);
        CHECK( *optional_value == expected );
        optional_value = convert::to_non_temporal_type(invalid_timepoint, value);
        CHECK( *optional_value == expected );
    }

    SECTION("array_type")
    {
        attribute_t::array_type    array{1,2,3};
        attribute_t::temporal_type value(array);
        attribute_t::type          expected(array);
        auto optional_value = convert::to_non_temporal_type(timepoint, value);
        CHECK( *optional_value == expected );
        optional_value = convert::to_non_temporal_type(invalid_timepoint, value);
        CHECK( *optional_value == expected );
    }

    SECTION("temporal_value_type")
    {
        attribute_t::temporal_value_type temporal_value;
        temporal_value.insert(timepoint, 7);
        attribute_t::temporal_type value(temporal_value);
        attribute_t::type expected = 7;
        auto optional_value = convert::to_non_temporal_type(timepoint, value);
        CHECK( *optional_value == expected );
        optional_value = convert::to_non_temporal_type(invalid_timepoint, value);
        CHECK_FALSE( optional_value );
    }

    SECTION("temporal_array_type")
    {
        attribute_t::temporal_array_type temporal_array;
        {
            attribute_t::temporal_value_type temporal_value;
            temporal_value.insert(timepoint, 1);
            temporal_array.push_back(temporal_value);
        }
        {
            attribute_t::temporal_value_type temporal_value;
            temporal_value.insert(timepoint, 2);
            temporal_array.push_back(temporal_value);
        }
        attribute_t::temporal_type value(temporal_array);
        attribute_t::array_type    array{1,2};
        attribute_t::type          expected(array);
        auto optional_value = convert::to_non_temporal_type(timepoint, value);
        CHECK( *optional_value == expected );
        optional_value = convert::to_non_temporal_type(invalid_timepoint, value);
        CHECK_FALSE( optional_value );
    }
}
