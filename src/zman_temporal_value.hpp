#ifndef ZMAN_TEMPORAL_VALUE_HPP
#define ZMAN_TEMPORAL_VALUE_HPP

namespace zman {

template<class TIME_POINT, class VALUE>
class temporal_value
{
public:
    using time_point_type = TIME_POINT;
    using value_type      = VALUE;

    temporal_value() = default;

    temporal_value(time_point_type time_point, value_type value)
    : time_point_(time_point) 
    , value_(value) 
    {
    }

    const time_point_type& time_point() const { return time_point_; }
    const value_type&      value()      const { return value_;       } 

    friend bool operator==(const temporal_value& lhs, const temporal_value& rhs)
    {
        return lhs.time_point_ == rhs.time_point_;
    }

    friend bool operator!=(const temporal_value& lhs, const temporal_value& rhs)
    {
        return lhs.time_point_ != rhs.time_point_;
    }

    friend bool operator<(const temporal_value& lhs, const temporal_value& rhs)
    {
        return lhs.time_point_ < rhs.time_point_;
    }

    friend bool operator<=(const temporal_value& lhs, const temporal_value& rhs)
    {
        return lhs.time_point_ <= rhs.time_point_;
    }

    friend bool operator>(const temporal_value& lhs, const temporal_value& rhs)
    {
        return lhs.time_point_ > rhs.time_point_;
    }

    friend bool operator>=(const temporal_value& lhs, const temporal_value& rhs)
    {
        return lhs.time_point_ >= rhs.time_point_;
    }

private:
    time_point_type time_point_;
    value_type      value_;
}; 

}

#endif
