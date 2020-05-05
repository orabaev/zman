#ifndef ZMAN_TEMPORAL_CONVERT_VALUE_HPP
#define ZMAN_TEMPORAL_CONVERT_VALUE_HPP

#include "zman_attribute.hpp"
#include "zman_attribute_map.hpp"
#include "zman_entity.hpp"

namespace zman {

template<typename T> struct is_variant : std::false_type {};

template<typename ...Args>
struct is_variant<std::variant<Args...>> : std::true_type {};

template<typename T>
inline constexpr bool is_variant_v=is_variant<T>::value;

template<
      class NAMESPACE
    , class ID
    , class TIMEPOINT
    , class KEY
    , class VALUE
>
struct temporal_convert
{
    using namespace_type              = NAMESPACE;
    using id_type                     = ID;
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
    using entity_type                 = entity<namespace_type, id_type, timepoint_type>;

    static std::optional<typename entity_type::ptr_type> to_non_temporal_type(
          const timepoint_type&                 timepoint
        , const typename entity_type::ptr_type& entity_ptr
    )
    {
        if (!entity_ptr) return std::nullopt;
        auto ptr = entity_ptr->snap(timepoint);
        if (!ptr) return std::nullopt;
        return std::optional<typename entity_type::ptr_type>(ptr);
    }

    template<class NON_TEMPORAL_TYPE>
    static std::optional<NON_TEMPORAL_TYPE> to_non_temporal_type(
          const timepoint_type&    timepoint
        , const NON_TEMPORAL_TYPE& value
    )
    {
        if constexpr (is_variant_v<NON_TEMPORAL_TYPE>)
        {
            std::optional<NON_TEMPORAL_TYPE> ret;
            std::visit([&timepoint, &ret](auto&& arg){
                ret = to_non_temporal_type(timepoint, arg);
            }, value);  
            return ret;
        }
        {
            return std::optional<NON_TEMPORAL_TYPE>(value);
        }
    }

    static std::optional<value_type> to_non_temporal_type(
          const timepoint_type&      timepoint
        , const temporal_value_type& temporal_value
    )
    {
        auto ptr = temporal_value.find(timepoint);
        return ptr ? std::optional<value_type>(*ptr) : std::nullopt;
    }

    static std::optional<array_type> to_non_temporal_type(
          const timepoint_type&      timepoint
        , const temporal_array_type& temporal_array
    )
    {
        array_type array;
        for (auto& temporal_value : temporal_array)
        {
            auto optional_value = to_non_temporal_type(timepoint, temporal_value);
            if (optional_value) array.push_back(std::move(*optional_value)); 
        } 
        
        return !array.empty() ? std::optional<array_type>(std::move(array)) : std::nullopt;
    }

    static std::optional<attribute_type> to_non_temporal_type(
          const timepoint_type& timepoint
        , const attribute_type& non_temporal_attribute
    )
    {
        std::optional<attribute_type> ret;
        std::visit([&timepoint, &ret](auto&& arg){
            auto optional_value = to_non_temporal_type(timepoint, arg);
            ret = optional_value 
                   ? std::optional<attribute_type>(std::move(*optional_value)) 
                   : std::nullopt;
            
        }, non_temporal_attribute);  
        return ret;
    }

    static std::optional<attribute_type> to_non_temporal_type(
          const timepoint_type&          timepoint
        , const attribute_temporal_type& temporal_attribute
    )
    {
        std::optional<attribute_type> ret;
        std::visit([&timepoint, &ret](auto&& arg){
            auto optional_value = to_non_temporal_type(timepoint, arg);
            ret = optional_value 
                   ? std::optional<attribute_type>(std::move(*optional_value))
                   : std::nullopt;
            
        }, temporal_attribute);  
        return ret;
    } 

    static attribute_temporal_type to_temporal_type(attribute_type&& attribute)
    {
        attribute_temporal_type ret;
        std::visit([&ret](auto&& arg){
            ret = std::move(arg);
        }, std::move(attribute));  
        return ret;
    }

    static std::optional<attribute_map_type> to_non_temporal_type(
          const timepoint_type&              timepoint
        , const attribute_map_temporal_type& temporal_map
    )
    {
        attribute_map_type map;
        
        for (const auto& value : temporal_map)
        {
            auto optional_value = to_non_temporal_type(timepoint, value.second);
            if (optional_value) map[value.first] = std::move(*optional_value);
        }
        
        return !map.empty() ? std::optional<attribute_map_type>(std::move(map)) : std::nullopt;
    }

}; 

}

#endif
