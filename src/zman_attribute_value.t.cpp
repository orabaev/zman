#include "catch/catch.hpp"
#include "zman_attribute_value.hpp"
#include <type_traits>

using namespace zman;
using namespace std;

TEST_CASE("attribute_value")
{
    using time_point_type = int;
    using namespace_type  = string;
    using id_type         = int;
    using attribute_value_type = typename attribute_value<
          time_point_type
        , namespace_type
        , id_type
    >::type;

    static_assert( std::is_default_constructible<attribute_value_type>::value );
    static_assert( std::is_copy_constructible<attribute_value_type>::value    );
    static_assert( std::is_copy_assignable<attribute_value_type>::value       );
    static_assert( std::is_move_constructible<attribute_value_type>::value    );
    static_assert( std::is_move_assignable<attribute_value_type>::value       );
}
