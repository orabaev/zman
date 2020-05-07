#include "catch/catch.hpp"
#include "zman_temporal_convert.hpp"
#include "zman_test_util.t.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

using namespace_type  = string;
using id_type         = int;
using timepoint_type  = int;
using key_type        = string;
using value_type      = int;

using convert = temporal_convert<
      namespace_type
    , id_type
    , timepoint_type
    , key_type
    , value_type
>;

using attribute_t     = typename convert::attribute; 
using tu              = test_util<timepoint_type, key_type, value_type>;

TEST_CASE("temporal_convert.to_non_temporal_type.value")
{
    attribute_t::timepoint_type timepoint = 1;
    auto value = tu::value(12);
    auto optional_value = convert::to_non_temporal_type(timepoint, value);
    CHECK( *optional_value == value );
}

TEST_CASE("temporal_convert.to_non_temporal_type.variant")
{
    attribute_t::timepoint_type timepoint = 1;
    variant<int,string> v1;
    v1 = "hello";
    auto v2 = convert::to_non_temporal_type(timepoint, v1);
    CHECK( v1 == v2 );
}

TEST_CASE("temporal_convert.to_non_temporal_type.entity.ptr")
{
    auto ptr = make_shared<convert::entity_type>("namespace", 1);
    timepoint_type timepoint = 1;
    auto optional_value = convert::to_non_temporal_type(timepoint, ptr);;
    CHECK_FALSE( optional_value );
}

TEST_CASE("temporal_convert.to_non_temporal_type.array")
{
    attribute_t::timepoint_type timepoint = 1;
    auto array = tu::array({1,2,3});
    auto optional_value = convert::to_non_temporal_type(timepoint, array);
    CHECK( *optional_value == array );
}

TEST_CASE("temporal_convert.to_non_temporal_type.attribute")
{
    attribute_t::timepoint_type timepoint = 1;

    SECTION("value_type")
    {
        attribute_t::type attribute = tu::value(12);
        auto optional_value = convert::to_non_temporal_type(timepoint, attribute);
        CHECK( *optional_value == attribute );
    }

    SECTION("array_type")
    {
        attribute_t::type attribute = tu::array({1,2,3});
        auto optional_value = convert::to_non_temporal_type(timepoint, attribute);
        CHECK( *optional_value == attribute);
    }
}

TEST_CASE("temporal_convert.to_non_temporal_type.attribute_map")
{
    attribute_t::timepoint_type timepoint = 1;
    convert::attribute_map_type map;
    map["key1"] = 1;
    map["key2"] = attribute_t::array_type{1,2,3};

    auto optional_value = convert::to_non_temporal_type(timepoint, map);
    CHECK( *optional_value == map );
}

TEST_CASE("temporal_convert.to_non_temporal_type.temporal_value")
{
    auto temporal_value = tu::temporal_value({{1,10},{3,std::nullopt}});

    attribute_t::timepoint_type timepoint = 1;
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

    temporal_array.emplace_back( tu::temporal_value({{1,10},{3,std::nullopt}}) );
    temporal_array.emplace_back( tu::temporal_value({{2,55},{4,std::nullopt}})  );

    attribute_t::timepoint_type timepoint = 1;
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
        attribute_t::temporal_type attribute = tu::temporal_value({{timepoint,7}});
        attribute_t::type expected = 7;
        auto optional_value = convert::to_non_temporal_type(timepoint, attribute);
        CHECK( *optional_value == expected );
        optional_value = convert::to_non_temporal_type(invalid_timepoint, attribute);
        CHECK_FALSE( optional_value );
    }

    SECTION("temporal_array_type")
    {
        attribute_t::temporal_array_type temporal_array;

        temporal_array.emplace_back( tu::temporal_value({{timepoint,1}}) );
        temporal_array.emplace_back( tu::temporal_value({{timepoint,2}}) );

        attribute_t::temporal_type attribute = temporal_array;
        attribute_t::array_type    array{1,2};
        attribute_t::type          expected(array);
        auto optional_value = convert::to_non_temporal_type(timepoint, attribute);
        CHECK( *optional_value == expected );
        optional_value = convert::to_non_temporal_type(invalid_timepoint, attribute);
        CHECK_FALSE( optional_value );
    }
}
