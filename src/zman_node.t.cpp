#include "catch/catch.hpp"
#include "zman_node.hpp"
#include <string>
#include <type_traits>

using namespace zman;
using namespace std;

using namespace_type     = string;
using id_type            = int;
using time_point_type    = int;
using key_type           = string;
using value_type         = int;

using node_type = node<
      namespace_type
    , id_type
    , time_point_type
    , key_type 
    , value_type
>;

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
