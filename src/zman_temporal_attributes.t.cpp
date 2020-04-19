#include "catch/catch.hpp"
#include "zman_temporal_attributes.hpp"
#include "zman_time_line.hpp"
#include <string>
#include <type_traits>

using namespace zman;
using namespace std;

using key_type                 = string;
using time_point_type          = int;
using value_type               = string;
using time_line_type           = time_line<time_point_type, value_type>;
using temporal_attributes_type = temporal_attributes<key_type, time_line_type>;

TEST_CASE("temporal_attributes.defaults")
{
    static_assert( std::is_default_constructible<temporal_attributes_type>::value );
    static_assert( std::is_copy_constructible<temporal_attributes_type>::value    );
    static_assert( std::is_move_constructible<temporal_attributes_type>::value    );
    static_assert( std::is_move_assignable<temporal_attributes_type>::value       );
}

TEST_CASE("temporal_attributes.empty")
{
    temporal_attributes_type attributes;
    CHECK(  attributes.get_value(1, "Key1") == nullptr );
    CHECK(  attributes.get_value(2, "Key1") == nullptr );
    CHECK(  attributes.get_value(1, "Key2") == nullptr );
}

TEST_CASE("temporal_attributes.set_value_from")
{
    temporal_attributes_type attributes;

    attributes.set_value_from(1948, "First Name", "Avram"  );
    attributes.set_value_from(2018, "First Name", "Avraham");

    for (int i = 0; i < 1948; ++i)
        CHECK( attributes.get_value(i, "First Name") == nullptr );

    for (int i = 1948; i < 2018; ++i)
        CHECK( *attributes.get_value(i, "First Name") == "Avram" );

    for (int i = 2018; i < 2030; ++i)
        CHECK( *attributes.get_value(i, "First Name") == "Avraham" );
}

TEST_CASE("temporal_attributes.set_value_to")
{
    temporal_attributes_type attributes;
    
    attributes.set_value_from(2010, "Status", "Consultant");    
    attributes.set_value_to  (2014, "Status"              );    
    attributes.set_value_from(2016, "Status", "Consultant");    
    attributes.set_value_from(2018, "Status", "Fulltime"  );    
    
    CHECK(  attributes.get_value(2009, "Status") == nullptr      );
    CHECK( *attributes.get_value(2010, "Status") == "Consultant" );
    CHECK( *attributes.get_value(2011, "Status") == "Consultant" );
    CHECK( *attributes.get_value(2012, "Status") == "Consultant" );
    CHECK( *attributes.get_value(2013, "Status") == "Consultant" );
    CHECK(  attributes.get_value(2014, "Status") == nullptr      );
    CHECK(  attributes.get_value(2015, "Status") == nullptr      );
    CHECK( *attributes.get_value(2016, "Status") == "Consultant" );
    CHECK( *attributes.get_value(2017, "Status") == "Consultant" );
    CHECK( *attributes.get_value(2018, "Status") == "Fulltime"   );
    CHECK( *attributes.get_value(2019, "Status") == "Fulltime"   );
    CHECK( *attributes.get_value(2020, "Status") == "Fulltime"   );
}

TEST_CASE("temporal_attributes.multiple_keys")
{
    temporal_attributes_type attributes;

    attributes.set_value_from(1942, "Name", "Cassius Clay");
    attributes.set_value_from(1961, "Name", "Muhammad Ali");

    attributes.set_value_from(1954, "Boxing Status", "Amateur");
    attributes.set_value_from(1961, "Boxing Status", "Professional");
    attributes.set_value_to(1981, "Boxing Status");
    
    CHECK(  attributes.get_value(1940, "Name")          == nullptr        );
    CHECK(  attributes.get_value(1940, "Boxing Status") == nullptr        );
    CHECK(  attributes.get_value(1941, "Name")          == nullptr        );
    CHECK(  attributes.get_value(1941, "Boxing Status") == nullptr        );
    CHECK( *attributes.get_value(1942, "Name")          == "Cassius Clay" );
    CHECK(  attributes.get_value(1942, "Boxing Status") == nullptr        );
    CHECK( *attributes.get_value(1948, "Name")          == "Cassius Clay" );
    CHECK(  attributes.get_value(1948, "Boxing Status") == nullptr        );
    CHECK( *attributes.get_value(1953, "Name")          == "Cassius Clay" );
    CHECK(  attributes.get_value(1953, "Boxing Status") == nullptr        );
    CHECK( *attributes.get_value(1954, "Name")          == "Cassius Clay" );
    CHECK( *attributes.get_value(1954, "Boxing Status") == "Amateur"      );
    CHECK( *attributes.get_value(1960, "Name")          == "Cassius Clay" );
    CHECK( *attributes.get_value(1960, "Boxing Status") == "Amateur"      );
    CHECK( *attributes.get_value(1961, "Name")          == "Muhammad Ali" );
    CHECK( *attributes.get_value(1961, "Boxing Status") == "Professional" );
    CHECK( *attributes.get_value(1962, "Name")          == "Muhammad Ali" );
    CHECK( *attributes.get_value(1962, "Boxing Status") == "Professional" );
    CHECK( *attributes.get_value(1980, "Name")          == "Muhammad Ali" );
    CHECK( *attributes.get_value(1980, "Boxing Status") == "Professional" );
    CHECK( *attributes.get_value(1981, "Name")          == "Muhammad Ali" );
    CHECK(  attributes.get_value(1981, "Boxing Status") == nullptr        );
    CHECK( *attributes.get_value(1990, "Name")          == "Muhammad Ali" );
    CHECK(  attributes.get_value(1990, "Boxing Status") == nullptr        );
}
