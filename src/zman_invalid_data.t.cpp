#include "catch/catch.hpp"
#include "zman_invalid_data.hpp"

using namespace zman;

TEST_CASE("invalid_data")
{
    CHECK( invalid_data<int>::value == 0 );
}

TEST_CASE("is_valid_data")
{
    CHECK( is_valid_data( 0) == false );
    CHECK( is_valid_data( 1) == true  );
    CHECK( is_valid_data(-1) == true  );
}
