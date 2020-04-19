#include "catch/catch.hpp"
#include "zman_time_line.hpp"
#include "zman_temporal_value.hpp"
#include <string>
#include <algorithm>
#include <utility>
#include <type_traits>

using namespace zman;
using namespace std;

TEST_CASE("time_line.defaults")
{
    using time_line_type = time_line<int, int>;

    static_assert( is_default_constructible<time_line_type>::value );
    static_assert( is_move_constructible<time_line_type>::value    );
    static_assert( is_move_assignable<time_line_type>::value       );
}

TEST_CASE("time_line.insert.from.to")
{
    using time_line_type   = time_line<int,string>;

    time_line_type time_line;
    const auto& content = time_line.content();

    time_line.insert(10, "from");
    time_line.insert(20);

    REQUIRE( content.size() == 2 );

    CHECK( content[0].time_point() == 10 );
    CHECK( content[1].time_point() == 20 );

    CHECK( content[0].value() == "from" );
    CHECK_FALSE( content[1].value() );
}

TEST_CASE("time_line.insert.when_content_is_empty")
{
    using time_line_type   = time_line<int,string>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.insert(10, "first") );
    CHECK_THROWS ( time_line.insert(10, "second") );

    REQUIRE( content.size() == 1 );

    CHECK( content[0].time_point() == 10 );
    CHECK( content[0].value() == "first" );
}

TEST_CASE("time_line.insert.lt_front")
{
    using time_line_type   = time_line<int,string>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.insert(10, "value1") );
    CHECK_NOTHROW( time_line.insert( 5, "value2") );
    CHECK_THROWS ( time_line.insert( 5, "value3") );
    CHECK_THROWS ( time_line.insert(10, "value4") );

    CHECK( content.size() == 2 );

    CHECK( content[0].time_point() ==  5 );
    CHECK( content[1].time_point() == 10 );

    CHECK( content[0].value() == "value2" );
    CHECK( content[1].value() == "value1" );

    CHECK_NOTHROW( time_line.insert(4, "value4") );
    CHECK_THROWS ( time_line.insert(4, "value5") );

    REQUIRE( content.size() == 3 );

    CHECK( content[0].time_point() ==  4 );
    CHECK( content[1].time_point() ==  5 );
    CHECK( content[2].time_point() == 10 );

    CHECK( content[0].value() == "value4" );
    CHECK( content[1].value() == "value2" );
    CHECK( content[2].value() == "value1" );
}

TEST_CASE("time_line.insert.gt_back")
{
    using time_line_type   = time_line<int,string>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.insert(10, "value10") );
    CHECK_NOTHROW( time_line.insert(12, "value12") );
    CHECK_THROWS(  time_line.insert(10, "value10") );
    CHECK_THROWS(  time_line.insert(12, "value12") );
 
    REQUIRE( content.size() == 2 );

    CHECK( content[0].time_point() == 10 );
    CHECK( content[1].time_point() == 12 );

    CHECK( content[0].value() == "value10" );
    CHECK( content[1].value() == "value12" );
}

TEST_CASE("time_line.insert.between_values")
{
    using time_line_type   = time_line<int,int>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.insert( 5, 5) );
    CHECK_NOTHROW( time_line.insert(10, 10) );
    CHECK_NOTHROW( time_line.insert( 7, 7) );
    CHECK_THROWS ( time_line.insert( 5, 6) );
    CHECK_THROWS ( time_line.insert(10, 11) );
    CHECK_THROWS ( time_line.insert( 7, 8) );

    REQUIRE( content.size() == 3 );

    CHECK( content[0].time_point() ==  5 );
    CHECK( content[1].time_point() ==  7 );
    CHECK( content[2].time_point() == 10 );

    CHECK( content[0].value() ==  5 );
    CHECK( content[1].value() ==  7 );
    CHECK( content[2].value() == 10 );


    CHECK_NOTHROW( time_line.insert(6, 6) );
    CHECK_THROWS ( time_line.insert(6, 7) );

    REQUIRE( content.size() == 4 );

    CHECK( content[0].time_point() ==  5 );
    CHECK( content[1].time_point() ==  6 );
    CHECK( content[2].time_point() ==  7 );
    CHECK( content[3].time_point() == 10 );

    CHECK( content[0].value() ==  5 );
    CHECK( content[1].value() ==  6 );
    CHECK( content[2].value() ==  7 );
    CHECK( content[3].value() == 10 );
}

TEST_CASE("time_line.insert.permutation")
{
    using time_line_type   = time_line<int,int>;
    using vector_type      = std::vector<pair<int,int>>;

    vector_type vec{ {1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7} }; 
    
    while( std::next_permutation(begin(vec), end(vec)) )
    {
        time_line_type time_line;
        for (const auto& value : vec) time_line.insert(value.first, value.second);
        const auto& content = time_line.content();

        for (auto i = 0; i < vec.size(); ++i)
        {
            CHECK( content.size() == vec.size() );
            CHECK( content[i].time_point() ==  i + 1 );
            CHECK( content[i].value() ==  i + 1 );
        }
    }
}

TEST_CASE("time_line.find_value.empty")
{
    using time_line_type   = time_line<int,int>;
    
    time_line_type time_line;

    CHECK( time_line.find( 1) == nullptr ); 
    CHECK( time_line.find( 5) == nullptr ); 
    CHECK( time_line.find( 7) == nullptr ); 
}
