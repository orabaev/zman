#ifndef ZMAN_TEMPORAL_CONVERT_VALUE_HPP
#define ZMAN_TEMPORAL_CONVERT_VALUE_HPP

#include "zman_attribute.hpp"
#include "zman_attribute_map.hpp"

namespace zman {

template<class TIMEPOINT, class KEY, class VALUE>
struct temporal_convert
{
    using timepoint_type              = TIMEPOINT; 
    using key_type                    = KEY;
    using value_type                  = VALUE; 
    using attribute                   = attribute<timepoint_type, value_type>; 
    using temporal_value_type         = typename attribute::temporal_value_type ;
    using array_type                  = typename attribute::array_type;
    using temporal_array_type         = typename attribute::temporal_array_type;
    using attribute_map               = attribute_map<timepoint_type, key_type, value_type>;
    using attribute_map_type          = typename attribute_map::type;
    using attribute_map_temporal_type = typename attribute_map::temporal_type;


    static std::optional<value_type> to_value_type(
          const timepoint_type&      timepoint
        , const temporal_value_type& temporal_value
    )
    {
        auto ptr = temporal_value.find(timepoint);
        return ptr ? std::optional<value_type>(*ptr) : std::nullopt;
    }

    static std::optional<array_type> to_array_type(
          const timepoint_type&      timepoint
        , const temporal_array_type& temporal_array
    )
    {
        array_type array;
        for (auto& temporal_value : temporal_array)
        {
            auto optional_value = to_value_type(timepoint, temporal_value);
            if (optional_value) array.push_back(*optional_value); 
        } 
        
        return !array.empty() ? std::optional<array_type>(std::move(array)) : std::nullopt;
    }
}; 

}

#endif
