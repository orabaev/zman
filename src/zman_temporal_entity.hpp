#ifndef ZMAN_TEMPORAL_ENTITY_HPP
#define ZMAN_TEMPORAL_ENTITY_HPP

#include "zman_time_line.hpp"

namespace zman {

template<class ID, class TIME_POINT>
class temporal_entity
{
public:
    using id_type           = ID;
    using time_point_type   = TIME_POINT;
    using temporal_id_type  = temporal_id<id_type, time_point_type>;
    using time_line_type    = time_line<temporal_id_type>;
    
    temporal_entity() = default;

    temporal_entity(id_type id)
    : id_(id)
    {
    }

    const time_line_type& time_line() const { return time_line_; }
          time_line_type& time_line()       { return time_line_; }

    const id_type& id() const { return id_; } 

private:
    id_type         id_;
    time_line_type  time_line_;
}; 

}

#endif
