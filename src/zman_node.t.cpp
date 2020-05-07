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
using entity_type        = entity<namespace_type, id_type, timepoint_type>;
using entity_ptr_type    = typename entity_type::ptr_type;
using complex_value_type = variant<int, entity_ptr_type>;

using node_type = node<
      namespace_type
    , id_type
    , timepoint_type
    , key_type 
    , value_type
>;

using complex_node_type = node<
      namespace_type
    , id_type
    , timepoint_type
    , key_type 
    , complex_value_type
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

TEST_CASE("node.snap")
{
    node_type node("namespace.node", 1);
    node.set_attribute_value("key1", tu::value(12)); 
    node.set_attribute_value("key2", tu::temporal_value({{1,5},{3,7}}) ); 
    
    auto ptr = node.snap(3);
    CHECK( ptr );

    auto node_ptr = static_cast<node_type*>(ptr.get());
    attribute_t::type expected = tu::value(12);
    auto optional_value = node_ptr->get_attribute_value(10, "key1");
    CHECK( expected == optional_value ); 

    expected = tu::value(7);
    optional_value = node_ptr->get_attribute_value(10, "key2");
    CHECK( expected == optional_value );
}

TEST_CASE("node.complex_value_type")
{
    using ctu = test_util<timepoint_type, key_type, complex_value_type>;

    complex_node_type node("namespace.complex.node", 0);

    node.set_attribute_value("key1", ctu::value(0)); 
    node.set_attribute_value("key2", ctu::temporal_value({{1,5},{3,7}}) ); 

    auto ptr1 = make_shared<complex_node_type>("namespace.complex.node", 1);
    ptr1->set_attribute_value("1", ctu::value(1)); 
    ptr1->set_attribute_value("2", ctu::temporal_value({{1,50},{3,70}}) ); 

    auto ptr2 = make_shared<complex_node_type>("namespace.complex.node", 2);
    ptr2->set_attribute_value("1", ctu::value(2)); 
    ptr2->set_attribute_value("2", ctu::temporal_value({{1,500},{3,700}}) ); 

    node.set_attribute_value("key3", ctu::value(ptr1));
    node.set_attribute_value("key4", ctu::temporal_value({{1,ptr1},{3,ptr2}}) ); 

    auto entity_snapped_ptr = node.snap(3);
    auto node_snapped_ptr = static_cast<complex_node_type*>(entity_snapped_ptr.get());
    
    SECTION("key1")
    {
        auto  attribute_value = node_snapped_ptr->get_attribute_value(0, "key1");
        auto& complex_value = std::get<complex_value_type>(*attribute_value); 
        int  value = std::get<int>(complex_value); 
        CHECK( value == 0 ); 
    }
    SECTION("key2")
    {
        auto  attribute_value = node_snapped_ptr->get_attribute_value(0, "key2");
        auto& complex_value = std::get<complex_value_type>(*attribute_value); 
        int  value = std::get<int>(complex_value); 
        CHECK( value == 7 ); 
    }
    SECTION("key3")
    {
        auto  attribute_value = node_snapped_ptr->get_attribute_value(0, "key3");
        auto& complex_value = std::get<complex_value_type>(*attribute_value); 
        auto& entity = std::get<entity_ptr_type>(complex_value); 
        auto  value = static_cast<complex_node_type*>(entity.get());
        SECTION("1")
        {
            auto attribute_value = value->get_attribute_value(0, "1");
            auto& complex_value = std::get<complex_value_type>(*attribute_value); 
            int  sub_value = std::get<int>(complex_value); 
            CHECK( sub_value == 1 );           
        } 
        SECTION("2")
        {
            auto attribute_value = value->get_attribute_value(0, "2");
            auto& complex_value = std::get<complex_value_type>(*attribute_value); 
            int  sub_value = std::get<int>(complex_value); 
            CHECK( sub_value == 70 );           
        }
    }
    SECTION("key4")
    {
        auto  attribute_value = node_snapped_ptr->get_attribute_value(0, "key4");
        auto& complex_value = std::get<complex_value_type>(*attribute_value); 
        auto& entity = std::get<entity_ptr_type>(complex_value); 
        auto  value = static_cast<complex_node_type*>(entity.get());
        SECTION("1")
        {
            auto attribute_value = value->get_attribute_value(0, "1");
            auto& complex_value = std::get<complex_value_type>(*attribute_value); 
            int  sub_value = std::get<int>(complex_value); 
            CHECK( sub_value == 2 );           
        } 
        SECTION("2")
        {
            auto attribute_value = value->get_attribute_value(0, "2");
            CHECK( attribute_value );
            auto& complex_value = std::get<complex_value_type>(*attribute_value); 
            int  sub_value = std::get<int>(complex_value); 
            CHECK( sub_value == 700 );           
        }
    }
}
