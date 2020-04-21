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
