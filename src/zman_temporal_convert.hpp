#ifndef ZMAN_TEMPORAL_CONVERT_VALUE_HPP
#define ZMAN_TEMPORAL_CONVERT_VALUE_HPP

#include "zman_attribute_value.hpp"

namespace zman {

template<class TIMEPOINT, class VALUE>
struct temporal_convert
{
    using attribute_value_type = attribute_value<TIMEPOINT, VALUE>; 
    using timepoint_type                = TIMEPOINT; 
    using value_type                    = VALUE; 
    using temporal_value_type           = typename attribute_value_type::temporal_value_type ;
    using array_type                    = typename attribute_value_type::array_type;
    using temporal_array_type           = typename attribute_value_type::temporal_array_type;

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
