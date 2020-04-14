#ifndef ZMAN_TEMPORAL_ID_HPP
#define ZMAN_TEMPORAL_ID_HPP

namespace zman {

template<class ID, class TIME_POINT>
class temporal_id
{
public:
    using id_type         = ID;
    using time_point_type = TIME_POINT;

    temporal_id() = default;

    temporal_id(id_type id, time_point_type time_point)
    : id_(id) 
    , time_point_(time_point) 
    {
    }

    const id_type& id() const { return id_; } 
    const time_point_type& time_point() const { return time_point_; }

    friend bool operator==(const temporal_id& lhs, const temporal_id& rhs)
    {
        return lhs.time_point_ == rhs.time_point_;
    }

    friend bool operator!=(const temporal_id& lhs, const temporal_id& rhs)
    {
        return lhs.time_point_ != rhs.time_point_;
    }

    friend bool operator<(const temporal_id& lhs, const temporal_id& rhs)
    {
        return lhs.time_point_ < rhs.time_point_;
    }

    friend bool operator<=(const temporal_id& lhs, const temporal_id& rhs)
    {
        return lhs.time_point_ <= rhs.time_point_;
    }

    friend bool operator>(const temporal_id& lhs, const temporal_id& rhs)
    {
        return lhs.time_point_ > rhs.time_point_;
    }

    friend bool operator>=(const temporal_id& lhs, const temporal_id& rhs)
    {
        return lhs.time_point_ >= rhs.time_point_;
    }

private:
    id_type          id_;
    time_point_type  time_point_;
}; 

}

#endif
