#ifndef ZMAN_TEMPORAL_ATTRIBUTE_VALUE_HPP
#define ZMAN_TEMPORAL_ATTRIBUTE_VALUE_HPP

#include "zman_time_line.hpp"
#include <vector>
#include <unordered_map>
#include <variant>

namespace zman {

template<class TIMEPOINT, class KEY, class VALUE>
struct attribute_value
{
    attribute_value() = delete;
    
    using timepoint_type                = TIMEPOINT; 
    using key_type                      = KEY;
    using value_type                    = VALUE; 
    using temporal_value_type           = time_line<timepoint_type, value_type>;
    using array_type                    = std::vector<value_type>;
    using temporal_array_type           = std::vector<temporal_value_type>;
    using unordered_map_type            = std::unordered_map<key_type, value_type>;
    using temporal_unordered_map_type   = std::unordered_map<key_type, temporal_value_type>;

    using type = std::variant<
          value_type
        , temporal_value_type 
        , array_type
        , temporal_array_type
        , unordered_map_type
        , temporal_unordered_map_type
    >;
}; 

}

#endif
