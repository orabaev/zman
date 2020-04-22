#ifndef ZMAN_TEMPORAL_RELATIONSHIP_HPP
#define ZMAN_TEMPORAL_RELATIONSHIP_HPP

namespace zman {

template<class TEMPORAL_ENTITY, class TIMELINE>
class temporal_relationship : public TEMPORAL_ENTITY
{
public:
    using base_type                = TEMPORAL_ENTITY;
    using time_line_type           = TIMELINE;
    using node_type                = typename time_line_type::value_type; 
    using id_type                  = typename base_type::id_type;
    using label_type               = typename base_type::label_type;
    using temporal_attributes_type = typename base_type::temporal_attributes_type;
    using time_point_type          = typename base_type::time_point_type;
    using attribute_key_type       = typename base_type::attribute_key_type;
    using attribute_value_type     = typename base_type::attribute_value_type;

    temporal_relationship(
          const id_type&    id
        , const label_type& label
        , const node_type*  node
    )
    : base_type(id, label)
    , first_node_(node)
    , time_line_()
    {
    }

    const node_type* first_node() const { return first_node_; }

    const node_type* second_node(const time_point_type& time_point) const
    {
        return time_line_.find(time_point);
    }

private:
    const node_type* first_node_;
    time_line_type   time_line_; 
}; 

}

#endif
