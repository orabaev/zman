#ifndef ZMAN_TEST_UTIL_T_HPP
#define ZMAN_TEST_UTIL_T_HPP

#include "zman_attribute.hpp"
#include "zman_attribute_map.hpp"

namespace zman {

template<class TIMEPOINT, class KEY, class VALUE>
struct test_util
{
    using timepoint_type              = TIMEPOINT; 
    using key_type                    = KEY;
    using value_type                  = VALUE; 
    using attribute                   = attribute<timepoint_type, value_type>; 
    using attribute_type              = typename attribute::type; 
    using attribute_temporal_type     = typename attribute::temporal_type; 
    using temporal_value_type         = typename attribute::temporal_value_type ;
    using array_type                  = typename attribute::array_type;
    using temporal_array_type         = typename attribute::temporal_array_type;
    using attribute_map               = attribute_map<timepoint_type, key_type, value_type>;
    using attribute_map_type          = typename attribute_map::type;
    using attribute_map_temporal_type = typename attribute_map::temporal_type;

    static value_type value(const value_type& value)
    {
        return value;
    }

    static array_type array(std::initializer_list<value_type> list) 
    {
        return array_type(list);
    }

    static attribute_type attribute_as_value(const value_type& val)
    {
        return attribute_type(value(val));
    }

    static attribute_type attribute_as_array(std::initializer_list<value_type> list)
    {
        return attribute_type(array(list));
    }

    static temporal_value_type temporal_value(
        std::initializer_list<typename temporal_value_type::temporal_value_type> list
    )
    {
        temporal_value_type timeline;
        for (auto val : list)
        {
            if (val.value()) timeline.insert(val.time_point(), *val.value());
            else             timeline.insert(val.time_point());

        }
        return timeline;
    }

};

}

#endif
