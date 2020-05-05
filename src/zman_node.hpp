#ifndef ZMAN_NODE_HPP
#define ZMAN_NODE_HPP 

#include "zman_entity.hpp"
#include "zman_attribute_map.hpp"
#include "zman_temporal_convert.hpp"
#include <optional>

namespace zman {

template<
      class NAMESPACE
    , class ID
    , class TIMEPOINT
    , class KEY
    , class VALUE
>
class node : public entity<NAMESPACE, ID, TIMEPOINT>
{
public:
    using base_type                = entity<NAMESPACE, ID, TIMEPOINT>;
    using namespace_type           = NAMESPACE;
    using id_type                  = ID;
    using timepoint_type           = TIMEPOINT; 
    using key_type                 = KEY;
    using value_type               = VALUE;
    using attribute_map            = attribute_map<timepoint_type, key_type, value_type>;
    using map_type                 = typename attribute_map::temporal_type;
    using attribute                = typename attribute_map::attribute;
    using attribute_type           = typename attribute::type;
    using attribute_temporal_type  = typename attribute::temporal_type;
    using convert                  = temporal_convert<timepoint_type, key_type, value_type>; 
         
    node(
          const namespace_type& namespac
        , const id_type&        id
    )
    : entity<NAMESPACE, ID, TIMEPOINT>(namespac, id)
    {
    }

    virtual ~node() {} 

    void set_attribute_value(const key_type& key, const attribute_temporal_type& value)
    {
        attributes_[key] = value; 
    }

    void set_attribute_value(const key_type& key, attribute_temporal_type&& value)
    {
        attributes_[key] = std::move(value); 
    }

    std::optional<attribute_type> get_attribute_value(
          const timepoint_type& timepoint
        , const key_type& key
    ) const
    {
        auto it = attributes_.find(key);
        if (it == attributes_.end()) return std::nullopt;
        return convert::to_non_temporal_type(timepoint, it->second);
    }

private:
    map_type attributes_;
}; 

}

#endif
