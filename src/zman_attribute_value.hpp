#ifndef ZMAN_TEMPORAL_ATTRIBUTE_VALUE_HPP
#define ZMAN_TEMPORAL_ATTRIBUTE_VALUE_HPP

#include "zman_time_line.hpp"
#include <vector>
#include <variant>
#include <optional>

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

    using type = std::variant<
          value_type
        , array_type
    >;

    using temporal_type = std::variant<
          value_type
        , temporal_value_type 
        , array_type
        , temporal_array_type
    >;

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
