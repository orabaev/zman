#include "catch/catch.hpp"
#include "zman_temporal_entity.hpp"
#include "zman_time_line.hpp"
#include "zman_temporal_attributes.hpp"
#include "zman_temporal_node.hpp"

#include <string>
#include <type_traits>

using namespace zman;
using namespace std;

using key_type                   = string;
using time_point_type            = int;
using value_type                 = string;
using time_line_type             = time_line<time_point_type, value_type>;
using temporal_attributes_type   = temporal_attributes<key_type, time_line_type>;
using id_type                    = int;
using label_type                 = string;
using temporal_entity_type       = temporal_entity<id_type, label_type, temporal_attributes_type>;
using node_time_line_type        = time_line<time_point_type, int>;
using node_type                  = int;
using temporal_node_type         = temporal_node<temporal_entity_type>;
using temporal_relationship_type = typename temporal_node_type::relationship_type; 
using temporal_node_ptr          = std::shared_ptr<temporal_node_type>;

TEST_CASE("temporal_relationship.defaults")
{
    static_assert( std::is_move_constructible<temporal_relationship_type>::value );
    static_assert( std::is_move_assignable<temporal_relationship_type>::value    );
}

TEST_CASE("temporal_relationship.ctor")
{
    id_type     id    = 12;
    label_type  label = "label";
    temporal_relationship_type relationship(id, label);

    CHECK( id    == relationship.id()    );
    CHECK( label == relationship.label() );

    time_point_type time_point = 1;
    CHECK( relationship.find_node(time_point) == nullptr );
}

TEST_CASE("temporal_relationship.insert_node_from")
{
    temporal_relationship_type relationship(101, "label");

    auto node = make_shared<temporal_node_type>(201, "node");
    relationship.insert_node_from(1, node);
    CHECK( relationship.find_node(1)->id() == 201);
}

TEST_CASE("temporal_relationship.insert_to")
{
    temporal_relationship_type relationship(101, "label");

    auto node = make_shared<temporal_node_type>(201, "node");
    relationship.insert_node_from(1, node);
    CHECK( relationship.find_node(1)->id() == 201);
    CHECK( relationship.find_node(2)->id() == 201);
    relationship.insert_to(2);
    CHECK( relationship.find_node(2) == nullptr);
}

TEST_CASE("temporal_relationship.find_node")
{
    temporal_relationship_type relationship(101, "label");

    CHECK( relationship.find_node(1) == nullptr);
    
    {
        auto node = make_shared<temporal_node_type>(201, "node");
        relationship.insert_node_from(1, node);
        CHECK( relationship.find_node(1)->id() == 201);
    }

    CHECK( relationship.find_node(1) == nullptr);

}

