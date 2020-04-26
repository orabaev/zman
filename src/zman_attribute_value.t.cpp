#include "catch/catch.hpp"
#include "zman_attribute_value.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

TEST_CASE("attribute_value.type")
{
    using time_point_type = int;
    using namespace_type  = string;
    using id_type         = int;
    using type = typename attribute_value<
          time_point_type
        , namespace_type
        , id_type
    >::type;

    static_assert( std::is_default_constructible<type>::value );
    static_assert( std::is_copy_constructible<type>::value    );
    static_assert( std::is_copy_assignable<type>::value       );
    static_assert( std::is_move_constructible<type>::value    );
    static_assert( std::is_move_assignable<type>::value       );
}

TEST_CASE("attribute_value.temporal_type")
{
    using time_point_type = int;
    using namespace_type  = string;
    using id_type         = int;
    using type = typename attribute_value<
          time_point_type
        , namespace_type
        , id_type
    >::temporal_type;

    static_assert( std::is_default_constructible<type>::value );
    static_assert( std::is_copy_constructible<type>::value    );
    static_assert( std::is_copy_assignable<type>::value       );
    static_assert( std::is_move_constructible<type>::value    );
    static_assert( std::is_move_assignable<type>::value       );
}
