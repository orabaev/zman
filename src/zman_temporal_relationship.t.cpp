#include "catch/catch.hpp"
#include "zman_temporal_entity.hpp"
#include "zman_time_line.hpp"
#include "zman_temporal_attributes.hpp"
#include "zman_temporal_relationship.hpp"

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
using temporal_relationship_type = temporal_relationship<temporal_entity_type, node_time_line_type>;

TEST_CASE("temporal_relationship.defaults")
{
    static_assert( std::is_move_constructible<temporal_relationship_type>::value    );
    static_assert( std::is_move_assignable<temporal_relationship_type>::value       );
}

TEST_CASE("temporal_relationship.ctor")
{
    id_type     id    = 12;
    label_type  label = "label";
    node_type   node  = 1; 
    temporal_relationship_type relationship(id, label, node);

    CHECK( id    == relationship.id()          );
    CHECK( label == relationship.label()       );
    CHECK( 1     == *relationship.first_node() );

    time_point_type time_point = 1;
    CHECK( relationship.second_node(time_point) == nullptr );
}

TEST_CASE("temporal_relationship.set_second_node_from")
{
    id_type     id    = 12;
    label_type  label = "label";
    node_type   node  = 1; 
    temporal_relationship_type relationship(id, label, node);

    relationship.set_second_node_from(1, 10);
    CHECK( *relationship.second_node(1) == 10 );
}

TEST_CASE("temporal_relationship.set_second_node_to")
{
    id_type     id    = 12;
    label_type  label = "label";
    node_type   node  = 1; 
    temporal_relationship_type relationship(id, label, node);

    relationship.set_second_node_from(1, 10);
    CHECK( *relationship.second_node(1) == 10      );
    CHECK( *relationship.second_node(2) == 10      );

    relationship.set_second_node_to(2);
    CHECK(  relationship.second_node(2) == nullptr );
}

TEST_CASE("temporal_relationship.second_node")
{
    id_type     id    = 12;
    label_type  label = "label";
    node_type   node  = 1; 
    temporal_relationship_type relationship(id, label, node);

    CHECK(  relationship.second_node(1) == nullptr );
    relationship.set_second_node_from(1, 10);
    CHECK( *relationship.second_node(1) == 10 );
    CHECK( *relationship.second_node(2) == 10 );
    CHECK(  relationship.second_node(0) == nullptr );
}
