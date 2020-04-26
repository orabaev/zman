#include "catch/catch.hpp"
#include "zman_entity.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

TEST_CASE("entity.defaults")
{
    using entity_type = entity<string, int>;
    static_assert( std::is_move_constructible<entity_type>::value    );
    static_assert( std::is_move_assignable<entity_type>::value       );
}

TEST_CASE("entity.ctor")
{
    using entity_type = entity<string, int>;
    int id = 1;
    string entity_namespace = "namespace";
    entity_type entity(entity_namespace, id);
}

TEST_CASE("entity.id")
{
    using entity_type = entity<string, int>;
    int id = 1;
    string entity_namespace = "namespace";
    entity_type entity(entity_namespace, id);
    CHECK( id == entity.id() );
}

TEST_CASE("entity.entity_namespace")
{
    using entity_type = entity<string, int>;
    int id = 1;
    string entity_namespace = "namespace";
    entity_type entity(entity_namespace, id);
    CHECK( entity_namespace == entity.entity_namespace() );
}
