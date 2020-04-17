#include "catch/catch.hpp"
#include "zman_time_line.hpp"
#include "zman_temporal_data.hpp"
#include <type_traits>
#include <algorithm>

using namespace zman;

TEST_CASE("time_line.defaults")
{
    using temporal_data_type = temporal_data<int,int>;
    using time_line_type   = time_line<temporal_data_type>;
    static_assert( std::is_default_constructible<time_line_type>::value );
    static_assert( std::is_move_constructible<time_line_type>::value );
    static_assert( std::is_move_assignable<time_line_type>::value );
}

TEST_CASE("time_line.invalid_data")
{
    using temporal_data_type = temporal_data<int,int>;
    using time_line_type   = time_line<temporal_data_type>;
    CHECK( time_line_type::invalid_data() == invalid_data<int>::value );
}

TEST_CASE("time_line.add_data.when_content_is_empty")
{
    using temporal_data_type = temporal_data<int,int>;
    using time_line_type   = time_line<temporal_data_type>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.add_data(1, 10) );
    CHECK_THROWS ( time_line.add_data(1, 10) );
    CHECK( content.size() == 1 );
    CHECK( content[0].time_point() == 10 );
}

TEST_CASE("time_line.add_data.lt_front")
{
    using temporal_data_type = temporal_data<int,int>;
    using time_line_type   = time_line<temporal_data_type>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.add_data(1, 10) );
    CHECK_NOTHROW( time_line.add_data(1,  5) );
    CHECK_THROWS ( time_line.add_data(1,  5) );
    CHECK_THROWS ( time_line.add_data(1, 10) );

    CHECK( content.size() == 2 );
    CHECK( content[0].time_point() ==  5 );
    CHECK( content[1].time_point() == 10 );

    CHECK_NOTHROW( time_line.add_data(1,  4) );
    CHECK_THROWS ( time_line.add_data(1,  4) );

    CHECK( content.size() == 3 );
    CHECK( content[0].time_point() ==  4 );
    CHECK( content[1].time_point() ==  5 );
    CHECK( content[2].time_point() == 10 );
}

TEST_CASE("time_line.add_data.gt_back")
{
    using temporal_data_type = temporal_data<int,int>;
    using time_line_type   = time_line<temporal_data_type>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.add_data(1, 10) );
    CHECK_NOTHROW( time_line.add_data(1, 12) );
    CHECK_THROWS ( time_line.add_data(1, 12) );
    CHECK_THROWS ( time_line.add_data(1, 10) );
    CHECK( content.size() == 2 );
    CHECK( content[0].time_point() == 10 );
    CHECK( content[1].time_point() == 12 );
}

TEST_CASE("time_line.add_data.between_values")
{
    using temporal_data_type = temporal_data<int,int>;
    using time_line_type   = time_line<temporal_data_type>;

    time_line_type time_line;
    const auto& content = time_line.content();

    CHECK_NOTHROW( time_line.add_data(1,  5) );
    CHECK_NOTHROW( time_line.add_data(1, 10) );
    CHECK_NOTHROW( time_line.add_data(1,  7) );
    CHECK_THROWS ( time_line.add_data(1,  5) );
    CHECK_THROWS ( time_line.add_data(1, 10) );
    CHECK_THROWS ( time_line.add_data(1,  7) );

    CHECK( content.size() == 3 );
    CHECK( content[0].time_point() ==  5 );
    CHECK( content[1].time_point() ==  7 );
    CHECK( content[2].time_point() == 10 );


    CHECK_NOTHROW( time_line.add_data(1, 6) );
    CHECK_THROWS ( time_line.add_data(1, 6) );

    CHECK( content.size() == 4 );
    CHECK( content[0].time_point() ==  5 );
    CHECK( content[1].time_point() ==  6 );
    CHECK( content[2].time_point() ==  7 );
    CHECK( content[3].time_point() == 10 );
}

TEST_CASE("time_line.add_data.permutation")
{
    using temporal_data_type = temporal_data<int,int>;
    using time_line_type   = time_line<temporal_data_type>;
    using vector_type      = std::vector<temporal_data_type>;

    vector_type vec{ {1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7} }; 
    
    while( std::next_permutation(begin(vec), end(vec)) )
    {
        time_line_type time_line;
        for (const auto& data : vec) time_line.add_data(data.data(), data.time_point());
        const auto& content = time_line.content();

        for (auto i = 0; i < vec.size(); ++i)
        {
            CHECK( content.size() == vec.size() );
            CHECK( content[i].time_point() ==  i + 1 );
            CHECK( content[i].data()         ==  i + 1 );
        }
    }
}

TEST_CASE("time_line.find_data")
{
    using temporal_data_type = temporal_data<int,int>;
    using time_line_type   = time_line<temporal_data_type>;
    using vector_type      = std::vector<temporal_data_type>;

    vector_type vec{ {1,5},{2,10},{3,11},{4,17},{5,27},{6,28} }; 
    time_line_type time_line;
    for (const auto& data : vec) time_line.add_data(data.data(), data.time_point());
    
    CHECK( time_line.find_data( 4) == time_line.invalid_data() ); 
    CHECK( time_line.find_data( 5) == 1 ); 
    CHECK( time_line.find_data( 6) == 1 ); 
    CHECK( time_line.find_data( 9) == 1 ); 
    CHECK( time_line.find_data(10) == 2 ); 
    CHECK( time_line.find_data(11) == 3 ); 
    CHECK( time_line.find_data(12) == 3 ); 
    CHECK( time_line.find_data(13) == 3 ); 
    CHECK( time_line.find_data(14) == 3 ); 
    CHECK( time_line.find_data(17) == 4 ); 
    CHECK( time_line.find_data(18) == 4 ); 
    CHECK( time_line.find_data(19) == 4 ); 
    CHECK( time_line.find_data(25) == 4 ); 
    CHECK( time_line.find_data(26) == 4 ); 
    CHECK( time_line.find_data(27) == 5 ); 
    CHECK( time_line.find_data(28) == 6 ); 
    CHECK( time_line.find_data(30) == 6 ); 
    CHECK( time_line.find_data(40) == 6 ); 
    CHECK( time_line.find_data(99) == 6 ); 
}

