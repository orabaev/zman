#include "catch/catch.hpp"
#include "zman_attribute_map.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

using time_point_type    = int;
using key_type           = string;
using value_type         = int;
using attribute_map_type = attribute_map<time_point_type, key_type, value_type>;

TEST_CASE("attribute_map.type")
{
    using type = typename attribute_map_type::type;

    static_assert( std::is_default_constructible<type>::value );
    static_assert( std::is_copy_constructible<type>::value    );
    static_assert( std::is_copy_assignable<type>::value       );
    static_assert( std::is_move_constructible<type>::value    );
    static_assert( std::is_move_assignable<type>::value       );
}

TEST_CASE("attribute_map.temporal_type")
{
    using type = typename attribute_map_type::temporal_type;

    static_assert( std::is_default_constructible<type>::value );
    static_assert( std::is_copy_constructible<type>::value    );
    static_assert( std::is_copy_assignable<type>::value       );
    static_assert( std::is_move_constructible<type>::value    );
    static_assert( std::is_move_assignable<type>::value       );
}
