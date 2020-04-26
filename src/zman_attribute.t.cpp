#include "catch/catch.hpp"
#include "zman_attribute.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

using time_point_type = int;
using value_type      = int;
using attribute_type  = attribute<time_point_type, value_type>;

TEST_CASE("attribute_value.type")
{
    using type = typename attribute_type::type;

    static_assert( std::is_default_constructible<type>::value );
    static_assert( std::is_copy_constructible<type>::value    );
    static_assert( std::is_copy_assignable<type>::value       );
    static_assert( std::is_move_constructible<type>::value    );
    static_assert( std::is_move_assignable<type>::value       );
}

TEST_CASE("attribute_value.temporal_type")
{
    using type = typename attribute_type::temporal_type;

    static_assert( std::is_default_constructible<type>::value );
    static_assert( std::is_copy_constructible<type>::value    );
    static_assert( std::is_copy_assignable<type>::value       );
    static_assert( std::is_move_constructible<type>::value    );
    static_assert( std::is_move_assignable<type>::value       );
}
