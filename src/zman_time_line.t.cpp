#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "zman_time_line.hpp"
#include "zman_temporal_id.hpp"
#include <type_traits>
#include <algorithm>

using namespace zman;

TEST_CASE("time_line.defaults")
{
    using temporal_id_type = temporal_id<int,int>;
    static_assert( std::is_default_constructible<time_line<temporal_id_type>>::value );
    static_assert( std::is_move_constructible<time_line<temporal_id_type>>::value );
}

TEST_CASE("time_line.add_id.invalid_id")
{
    using temporal_id_type = temporal_id<int,int>;
    using time_line_type   = time_line<temporal_id_type>;
    auto INVALID_ID  =  invalid_id<int>::value;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_THROWS( time_line.add_id(INVALID_ID, 1) );
    CHECK( content.size() == 0 );
}

TEST_CASE("time_line.add_id.when_content_is_empty")
{
    using temporal_id_type = temporal_id<int,int>;
    using time_line_type   = time_line<temporal_id_type>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.add_id(1, 10) );
    CHECK_THROWS ( time_line.add_id(1, 10) );
    CHECK( content.size() == 1 );
    CHECK( content[0].time_point() == 10 );
}

TEST_CASE("time_line.add_id.lt_front")
{
    using temporal_id_type = temporal_id<int,int>;
    using time_line_type   = time_line<temporal_id_type>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.add_id(1, 10) );
    CHECK_NOTHROW( time_line.add_id(1,  5) );
    CHECK_THROWS ( time_line.add_id(1,  5) );
    CHECK_THROWS ( time_line.add_id(1, 10) );

    CHECK( content.size() == 2 );
    CHECK( content[0].time_point() ==  5 );
    CHECK( content[1].time_point() == 10 );

    CHECK_NOTHROW( time_line.add_id(1,  4) );
    CHECK_THROWS ( time_line.add_id(1,  4) );

    CHECK( content.size() == 3 );
    CHECK( content[0].time_point() ==  4 );
    CHECK( content[1].time_point() ==  5 );
    CHECK( content[2].time_point() == 10 );
}

TEST_CASE("time_line.add_id.gt_back")
{
    using temporal_id_type = temporal_id<int,int>;
    using time_line_type   = time_line<temporal_id_type>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.add_id(1, 10) );
    CHECK_NOTHROW( time_line.add_id(1, 12) );
    CHECK_THROWS ( time_line.add_id(1, 12) );
    CHECK_THROWS ( time_line.add_id(1, 10) );
    CHECK( content.size() == 2 );
    CHECK( content[0].time_point() == 10 );
    CHECK( content[1].time_point() == 12 );
}

TEST_CASE("time_line.add_id.between_values")
{
    using temporal_id_type = temporal_id<int,int>;
    using time_line_type   = time_line<temporal_id_type>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.add_id(1,  5) );
    CHECK_NOTHROW( time_line.add_id(1, 10) );
    CHECK_NOTHROW( time_line.add_id(1,  7) );
    CHECK_THROWS ( time_line.add_id(1,  5) );
    CHECK_THROWS ( time_line.add_id(1, 10) );
    CHECK_THROWS ( time_line.add_id(1,  7) );

    CHECK( content.size() == 3 );
    CHECK( content[0].time_point() ==  5 );
    CHECK( content[1].time_point() ==  7 );
    CHECK( content[2].time_point() == 10 );


    CHECK_NOTHROW( time_line.add_id(1, 6) );
    CHECK_THROWS ( time_line.add_id(1, 6) );

    CHECK( content.size() == 4 );
    CHECK( content[0].time_point() ==  5 );
    CHECK( content[1].time_point() ==  6 );
    CHECK( content[2].time_point() ==  7 );
    CHECK( content[3].time_point() == 10 );
}

TEST_CASE("time_line.add_id.permutation")
{
    using temporal_id_type = temporal_id<int,int>;
    using time_line_type   = time_line<temporal_id_type>;
    using vector_type      = std::vector<temporal_id_type>;

    vector_type vec{ {1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7} }; 
    
    while( std::next_permutation(begin(vec), end(vec)) )
    {
        time_line_type time_line;
        for (const auto& tid : vec) time_line.add_id(tid.id(), tid.time_point());
        const auto& content = time_line.content();

        for (auto i = 0; i < vec.size(); ++i)
        {
            CHECK( content.size() == vec.size() );
            CHECK( content[i].time_point() ==  i + 1 );
            CHECK( content[i].id()         ==  i + 1 );
        }
    }
}
