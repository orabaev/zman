#include "catch/catch.hpp"
#include "zman_entity.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

using namespace_type = string;
using id_type        = int;
using timepoint_type = int;
using entity_type = entity<namespace_type, id_type, timepoint_type>;

TEST_CASE("entity.defaults")
{
    static_assert( std::is_move_constructible<entity_type>::value    );
    static_assert( std::is_move_assignable<entity_type>::value       );
}

TEST_CASE("entity.ctor")
{
    int id = 1;
    string entity_namespace = "namespace";
    entity_type entity(entity_namespace, id);
}

TEST_CASE("entity.id")
{
    int id = 1;
    string entity_namespace = "namespace";
    entity_type entity(entity_namespace, id);
    CHECK( id == entity.id() );
}

TEST_CASE("entity.entity_namespace")
{
    int id = 1;
    string entity_namespace = "namespace";
    entity_type entity(entity_namespace, id);
    CHECK( entity_namespace == entity.entity_namespace() );
}

TEST_CASE("entity.snap")
{
    int id = 1;
    string entity_namespace = "namespace";
    entity_type entity(entity_namespace, id);
    timepoint_type timepoint = 1;
    CHECK_FALSE( entity.snap(timepoint) );
}
