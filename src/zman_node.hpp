#ifndef ZMAN_NODE_HPP
#define ZMAN_NODE_HPP 

#include "zman_entity.hpp"
#include "zman_attribute_map.hpp"
#include <optional>

namespace zman {

template<
      class NAMESPACE
    , class ID
    , class TIMEPOINT
    , class KEY
    , class VALUE
>
class node : public entity<NAMESPACE, ID>
{
public:
    using namespace_type    = NAMESPACE;
    using id_type           = ID;
    using timepoint_type    = TIMEPOINT; 
    using key_type          = KEY;
    using attribute_map     = attribute_map<TIMEPOINT, KEY, VALUE>;
    using map_type          = typename attribute_map::temporal_type;
    using attribute         = typename attribute_map::attribute;
    using attribute_type    = typename attribute::temporal_type;

    node(
          const namespace_type& namespac
        , const id_type&        id
    )
    : entity<NAMESPACE, ID>(namespac, id)
    {
    }

    virtual ~node() {} 

    std::optional<attribute_type> get_attribute_value(
          const timepoint_type& timepoint
        , const key_type& key
    ) const;

    void set_attribute_value(const attribute_type& value);
    void set_attribute_value(attribute_type&& value);

    const map_type& get_attributes() const;

private:
    map_type attributes_;
}; 

}

#endif
