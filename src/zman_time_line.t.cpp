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

TEST_CASE("time_line.invalid_id")
{
    using temporal_id_type = temporal_id<int,int>;
    using time_line_type   = time_line<temporal_id_type>;
    CHECK( time_line_type::invalid_id() == invalid_id<int>::value );
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

TEST_CASE("time_line.find_id")
{
    using temporal_id_type = temporal_id<int,int>;
    using time_line_type   = time_line<temporal_id_type>;
    using vector_type      = std::vector<temporal_id_type>;

    vector_type vec{ {1,5},{2,10},{3,11},{4,17},{5,27},{6,28} }; 
    time_line_type time_line;
    for (const auto& tid : vec) time_line.add_id(tid.id(), tid.time_point());
    
    CHECK( time_line.find_id( 4) == time_line.invalid_id() ); 
    CHECK( time_line.find_id( 5) == 1 ); 
    CHECK( time_line.find_id( 6) == 1 ); 
    CHECK( time_line.find_id( 9) == 1 ); 
    CHECK( time_line.find_id(10) == 2 ); 
    CHECK( time_line.find_id(11) == 3 ); 
    CHECK( time_line.find_id(12) == 3 ); 
    CHECK( time_line.find_id(13) == 3 ); 
    CHECK( time_line.find_id(14) == 3 ); 
    CHECK( time_line.find_id(17) == 4 ); 
    CHECK( time_line.find_id(18) == 4 ); 
    CHECK( time_line.find_id(19) == 4 ); 
    CHECK( time_line.find_id(25) == 4 ); 
    CHECK( time_line.find_id(26) == 4 ); 
    CHECK( time_line.find_id(27) == 5 ); 
    CHECK( time_line.find_id(28) == 6 ); 
    CHECK( time_line.find_id(30) == 6 ); 
    CHECK( time_line.find_id(40) == 6 ); 
    CHECK( time_line.find_id(99) == 6 ); 
}

