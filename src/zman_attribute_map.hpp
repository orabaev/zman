#ifndef ZMAN_ATTRIBUTE_MAP_HPP
#define ZMAN_ATTRIBUTE_MAP_HPP

#include "zman_attribute_value.hpp"
#include <unordered_map>

namespace zman {

template<class TIMEPOINT, class KEY, class VALUE>
struct attribute_map
{
    attribute_map() = delete;

    using timepoint_type                = TIMEPOINT; 
    using key_type                      = KEY;
    using value_type                    = VALUE; 
    
    using attribute_value               = attribute_value<TIMEPOINT, VALUE>;
    using attribute_value_type          = typename attribute_value::type;
    using attribute_value_temporal_type = typename attribute_value::temporal_type;

    using type                          = std::unordered_map<KEY, attribute_value_type>;
    using temporal_type                 = std::unordered_map<KEY, attribute_value_temporal_type>;
}; 

}

#endif
