#include "catch/catch.hpp"
#include "zman_id.hpp"

using namespace zman;

TEST_CASE("invalid_id")
{
    CHECK( invalid_id<int>::value == 0 );
}

TEST_CASE("is_valid_id")
{
    CHECK( is_valid_id( 0) == false );
    CHECK( is_valid_id( 1) == true  );
    CHECK( is_valid_id(-1) == true  );
}
