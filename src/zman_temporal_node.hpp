#ifndef ZMAN_TEMPORAL_NODE_HPP
#define ZMAN_TEMPORAL_NODE_HPP

#include "zman_time_line.hpp"
#include <memory>
#include <unordered_map>

namespace zman {

template<class TEMPORAL_ENTITY>
class temporal_node : public TEMPORAL_ENTITY
{
public:
    class temporal_relationship : public TEMPORAL_ENTITY
    {
    public:
        using base_type                = TEMPORAL_ENTITY;
        using time_point_type          = typename base_type::time_point_type;
        using node_weak_ptr_type       = std::weak_ptr<temporal_node>;
        using time_line_type           = time_line<time_point_type, node_weak_ptr_type>;
        using node_type                = typename time_line_type::value_type; 
        using id_type                  = typename base_type::id_type;
        using label_type               = typename base_type::label_type;
        using temporal_attributes_type = typename base_type::temporal_attributes_type;
        using attribute_key_type       = typename base_type::attribute_key_type;
        using attribute_value_type     = typename base_type::attribute_value_type;

        temporal_relationship(
              const id_type&       id
            , const label_type&    label
        )
        : base_type(id, label)
        , time_line_()
        {
        }

        void insert_node_from(
              const time_point_type&    from
            , const node_weak_ptr_type& node
        )
        {
            time_line_.insert(from, node);
        }

        void insert_to(const time_point_type& to)
        {
            time_line_.insert(to);
        }

        const temporal_node* find_node(const time_point_type& time_point) const
        {
            auto ptr = time_line_.find(time_point);
            if (ptr && !ptr->expired())
            {
                return ptr->lock().get(); 
            }
            return nullptr;
        }

private:
    time_line_type time_line_; 
};

public:
    using base_type                = TEMPORAL_ENTITY;
    using id_type                  = typename base_type::id_type;
    using label_type               = typename base_type::label_type;
    using temporal_attributes_type = typename base_type::temporal_attributes_type;
    using time_point_type          = typename base_type::time_point_type;
    using attribute_key_type       = typename base_type::attribute_key_type;
    using attribute_value_type     = typename base_type::attribute_value_type;
    using relationship_type        = temporal_relationship;

    temporal_node(const id_type& id, const label_type& label)
    : base_type(id, label)
    {
    }

private:
     

};

/*
 
*/

}

#endif
