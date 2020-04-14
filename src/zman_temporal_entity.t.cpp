#include "catch/catch.hpp"
#include "zman_temporal_entity.hpp"
#include <type_traits>

using namespace zman;

TEST_CASE("temporal_entity.defaults")
{
    using temporal_entity_type = temporal_entity<int,int>;
    static_assert( std::is_default_constructible<temporal_entity_type>::value );
    static_assert( std::is_copy_constructible<temporal_entity_type>::value    );
    static_assert( std::is_move_constructible<temporal_entity_type>::value    );
}

TEST_CASE("temporal_entity.id")
{
    using temporal_entity_type = temporal_entity<int,int>;

    temporal_entity_type entity(12);
    CHECK( entity.id() == 12 );
}

TEST_CASE("temporal_entity.time_line")
{
    using temporal_entity_type = temporal_entity<int,int>;
    temporal_entity_type entity(12);
    
    auto& time_line_1 = entity.time_line(); 
    time_line_1.add_id(1,2); 
    
    auto& time_line_2 = entity.time_line(); 
    auto id = time_line_2.find_id(2); 
    CHECK( 1 == id );
}

