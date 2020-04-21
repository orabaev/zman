#ifndef ZMAN_TEMPORAL_ENTITY_HPP
#define ZMAN_TEMPORAL_ENTITY_HPP

#include <unordered_map>

namespace zman {

template<
      class ID
    , class LABEL 
    , class TEMPORAL_ATTRIBUTES
>
class temporal_entity
{
public:
    using id_type                  = ID;
    using label_type               = LABEL;
    using temporal_attributes_type = TEMPORAL_ATTRIBUTES;
    using time_line_type           = typename temporal_attributes_type::time_line_type;
    using time_point_type          = typename time_line_type::time_point_type;
    using attribute_key_type       = typename temporal_attributes_type::value_type;
    using attribute_value_type     = typename time_line_type::value_type;

    temporal_entity(const id_type& id, const label_type& label)
    : id_(id)
    , label_(label)
    , temporal_attributes_()
    {
    }

    const id_type&    id()    const { return id_;    }
    const label_type& label() const { return label_; }
    
     void set_attribute_value_from(
          const time_point_type&      from
        , const attribute_key_type&   key 
        , const attribute_value_type& value
    )
    {
        temporal_attributes_.set_value_from(from, key, value);
    }

    void set_attribute_value_to(
          const time_point_type&    to
        , const attribute_key_type& key 
    )
    {
        temporal_attributes_.set_value_to(to, key);
    }

    const attribute_value_type* get_attribute_value(
          const time_point_type&    time_point
        , const attribute_key_type& key 
    ) const
    {
        return temporal_attributes_.get_value(time_point, key);
    }

private:
    id_type                  id_;
    label_type               label_;
    temporal_attributes_type temporal_attributes_; 
}; 

}

#endif
