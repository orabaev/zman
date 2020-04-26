#include "catch/catch.hpp"
#include "zman_attribute_value.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

using time_point_type = int;
using key_type        = string;
using value_type      = int;
using attribute_t     = attribute_value<time_point_type, key_type, value_type>;

TEST_CASE("attribute_value.type")
{
    using type = typename attribute_t::type;

    static_assert( std::is_default_constructible<type>::value );
    static_assert( std::is_copy_constructible<type>::value    );
    static_assert( std::is_copy_assignable<type>::value       );
    static_assert( std::is_move_constructible<type>::value    );
    static_assert( std::is_move_assignable<type>::value       );
}

TEST_CASE("attribute_value.temporal_type")
{
    using type = typename attribute_t::temporal_type;

    static_assert( std::is_default_constructible<type>::value );
    static_assert( std::is_copy_constructible<type>::value    );
    static_assert( std::is_copy_assignable<type>::value       );
    static_assert( std::is_move_constructible<type>::value    );
    static_assert( std::is_move_assignable<type>::value       );
}

TEST_CASE("attribute_value.to_value_type")
{
    attribute_t::temporal_value_type temporal_value;    

    attribute_t::timepoint_type timepoint = 1;
    attribute_t::value_type     value     = 10;
    temporal_value.insert(timepoint, value);

    timepoint = 3;
    temporal_value.insert(timepoint);
    
    timepoint = 1;
    auto optional_value = attribute_t::to_value_type(timepoint, temporal_value);
    CHECK( *optional_value == 10 ); 

    timepoint = 2;
    optional_value = attribute_t::to_value_type(timepoint, temporal_value);
    CHECK( *optional_value == 10 ); 

    timepoint = 3;
    optional_value = attribute_t::to_value_type(timepoint, temporal_value);
    CHECK_FALSE( optional_value ); 
}

TEST_CASE("attribute_value.to_array_type")
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
    auto optional_value = attribute_t::to_array_type(timepoint, temporal_array);
    CHECK( (*optional_value).size() ==  1 ); 
    CHECK( (*optional_value)[0]     == 10 ); 

    timepoint = 2;
    optional_value = attribute_t::to_array_type(timepoint, temporal_array);
    CHECK( (*optional_value).size() ==  2 ); 
    CHECK( (*optional_value)[0]     == 10 );
    CHECK( (*optional_value)[1]     == 55 );

    timepoint = 3;
    optional_value = attribute_t::to_array_type(timepoint, temporal_array);
    CHECK( (*optional_value).size() ==  1 ); 
    CHECK( (*optional_value)[0]     == 55 );

    timepoint = 4;
    optional_value = attribute_t::to_array_type(timepoint, temporal_array);
    CHECK_FALSE( optional_value ); 
}
