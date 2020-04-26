#ifndef ZMAN_ATTRIBUTE_MAP_HPP
#define ZMAN_ATTRIBUTE_MAP_HPP

#include "zman_attribute.hpp"
#include <unordered_map>

namespace zman {

template<class TIMEPOINT, class KEY, class VALUE>
struct attribute_map
{
    attribute_map() = delete;

    using timepoint_type          = TIMEPOINT; 
    using key_type                = KEY;
    using value_type              = VALUE; 
    using attribute               = attribute<TIMEPOINT, VALUE>;
    using attribute_type          = typename attribute::type;
    using attribute_temporal_type = typename attribute::temporal_type;
    using type                    = std::unordered_map<KEY, attribute_type>;
    using temporal_type           = std::unordered_map<KEY, attribute_temporal_type>;
}; 

}

#endif
