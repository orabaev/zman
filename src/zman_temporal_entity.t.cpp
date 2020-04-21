#include "catch/catch.hpp"
#include "zman_temporal_entity.hpp"
#include "zman_time_line.hpp"
#include "zman_temporal_attributes.hpp"
#include <string>
#include <type_traits>

using namespace zman;
using namespace std;

using key_type                 = string;
using time_point_type          = int;
using value_type               = string;
using time_line_type           = time_line<time_point_type, value_type>;
using temporal_attributes_type = temporal_attributes<key_type, time_line_type>;
using id_type                  = int;
using label_type               = string;
using temporal_entity_type     = temporal_entity<id_type, label_type, temporal_attributes_type>;

TEST_CASE("temporal_entity.defaults")
{
    static_assert( std::is_copy_constructible<temporal_entity_type>::value    );
    static_assert( std::is_copy_assignable<temporal_entity_type>::value       );
    static_assert( std::is_move_constructible<temporal_entity_type>::value    );
    static_assert( std::is_move_assignable<temporal_entity_type>::value       );
}

TEST_CASE("temporal_entity.ctor.id.label")
{
    temporal_entity_type temporal_entity(12, "label");

    CHECK( temporal_entity.id()    == 12      );
    CHECK( temporal_entity.label() == "label" );
}

TEST_CASE("temporal_entity.set_attribute_value_from")
{
    temporal_entity_type temporal_entity(12, "label");

    temporal_entity.set_attribute_value_from(10, "phrase", "Hello World");
    temporal_entity.set_attribute_value_from(15, "phrase", "Good Day");
    
    CHECK( *temporal_entity.get_attribute_value(12, "phrase") == "Hello World");
    CHECK( *temporal_entity.get_attribute_value(15, "phrase") == "Good Day");
}

TEST_CASE("temporal_entity.set_attribute_value_to")
{
    temporal_entity_type temporal_entity(12, "label");

    temporal_entity.set_attribute_value_from(10, "phrase", "Hello World");
    temporal_entity.set_attribute_value_to(15, "phrase");
    
    CHECK( *temporal_entity.get_attribute_value(12, "phrase") == "Hello World" );
    CHECK(  temporal_entity.get_attribute_value(15, "phrase") == nullptr       );
}

TEST_CASE("temporal_entity.get_attribute_value")
{
    temporal_entity_type temporal_entity(12, "label");

    CHECK( temporal_entity.get_attribute_value(12, "phrase")   == nullptr);

    temporal_entity.set_attribute_value_from(10, "phrase", "Hello World");
    CHECK( *temporal_entity.get_attribute_value(12, "phrase") == "Hello World" );
}
