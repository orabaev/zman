#include "catch/catch.hpp"
#include "zman_node.hpp"
#include "zman_test_util.t.hpp"
#include "zman_temporal_convert.hpp"
#include <string>
#include <type_traits>

using namespace zman;
using namespace std;

using namespace_type     = string;
using id_type            = int;
using timepoint_type     = int;
using key_type           = string;
using value_type         = int;

using node_type = node<
      namespace_type
    , id_type
    , timepoint_type
    , key_type 
    , value_type
>;

using attribute_t = typename node_type::attribute;
using tu          = test_util<timepoint_type, key_type, value_type>;
using convert     = typename node_type::convert;

TEST_CASE("node.defaults")
{
    static_assert( std::is_move_constructible<node_type>::value    );
    static_assert( std::is_move_assignable<node_type>::value       );
}

TEST_CASE("node.ctor")
{
    node_type node("namespace.node", 1);
    CHECK( "namespace.node" == node.entity_namespace() );
    CHECK( 1 == node.id() );
}

TEST_CASE("node.set_attribute_value")
{
    node_type node("namespace.node", 1);
    attribute_t::temporal_type value = tu::value(12);

    node.set_attribute_value("key1", value); 
    attribute_t::type expected = tu::value(12);
    CHECK( expected == *node.get_attribute_value(1, "key1") ); 

    value = tu::value(15);
    node.set_attribute_value("key1", std::move(value)); 
    expected = tu::value(15);
    CHECK( expected == *node.get_attribute_value(1, "key1") ); 

    node.set_attribute_value("key1", tu::value(3)); 
    expected = tu::value(3);
    CHECK( expected == *node.get_attribute_value(1, "key1") ); 
}

TEST_CASE("node.get_attribute_value")
{
    node_type node("namespace.node", 1);
    node.set_attribute_value("key1", tu::value(12)); 
    node.set_attribute_value("key2", tu::temporal_value({{1,5},{3,7}}) ); 
    node.set_attribute_value("key3", tu::array({1,2,3}) ); 

    attribute_t::temporal_array_type array = {
          tu::temporal_value({{1,5},{2,7}})
        , tu::temporal_value({{1,2},{3,8}})
    };
      
    node.set_attribute_value("key4", std::move(array) ); 

    attribute_t::type expected = tu::value(12);
    CHECK( expected == *node.get_attribute_value(1, "key1") ); 

    expected = tu::value(5);
    CHECK( expected == *node.get_attribute_value(1, "key2") ); 
    expected = tu::value(7);
    CHECK( expected == *node.get_attribute_value(6, "key2") ); 
    
    expected = tu::array({1,2,3});
    CHECK( expected == *node.get_attribute_value(1, "key3") ); 

    expected = tu::array({5,2});
    CHECK( expected == *node.get_attribute_value(1, "key4") ); 
    expected = tu::array({7,2});
    CHECK( expected == *node.get_attribute_value(2, "key4") ); 
    expected = tu::array({7,8});
    CHECK( expected == *node.get_attribute_value(3, "key4") ); 
}
