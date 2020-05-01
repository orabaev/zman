#ifndef ZMAN_NODE_HPP
#define ZMAN_NODE_HPP 

#include "zman_entity.hpp"
#include "zman_attribute_map.hpp"

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
    using namespace_type        = NAMESPACE;
    using id_type               = ID;
    using timepoint_type        = TIMEPOINT; 
    using key_type              = KEY;
    using attribute_map         = attribute_map<TIMEPOINT, KEY, VALUE>;

    using attribute             = typename attribute_map::attribute;
    using attribute_type        = typename attribute::temporal_type;

/*
    using value_type            = typename attribute::value_type;  
    using temporal_value_type   = typename attribute::temporal_value_type;
    using array_type            = typename attribute::array_type;
    using temporal_array_type   = typename attribute::temporal_array_type;
*/

    node(
          const namespace_type& namespac
        , const id_type&        id
    )
    : entity<NAMESPACE, ID>(namespac, id)
    {
    }

    virtual ~node() {} 


private:
    using map_type = typename attribute_map::temporal_type;
    map_type attributes_;
}; 

}

#endif
