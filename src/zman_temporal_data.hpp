#ifndef ZMAN_TEMPORAL_DATA_HPP
#define ZMAN_TEMPORAL_DATA_HPP

namespace zman {

template<class DATA, class TIME_POINT>
class temporal_data
{
public:
    using data_type       = DATA;
    using time_point_type = TIME_POINT;

    temporal_data() = default;

    temporal_data(data_type data, time_point_type time_point)
    : data_(data) 
    , time_point_(time_point) 
    {
    }

    const data_type&       data()       const { return data_;       } 
    const time_point_type& time_point() const { return time_point_; }

    friend bool operator==(const temporal_data& lhs, const temporal_data& rhs)
    {
        return lhs.time_point_ == rhs.time_point_;
    }

    friend bool operator!=(const temporal_data& lhs, const temporal_data& rhs)
    {
        return lhs.time_point_ != rhs.time_point_;
    }

    friend bool operator<(const temporal_data& lhs, const temporal_data& rhs)
    {
        return lhs.time_point_ < rhs.time_point_;
    }

    friend bool operator<=(const temporal_data& lhs, const temporal_data& rhs)
    {
        return lhs.time_point_ <= rhs.time_point_;
    }

    friend bool operator>(const temporal_data& lhs, const temporal_data& rhs)
    {
        return lhs.time_point_ > rhs.time_point_;
    }

    friend bool operator>=(const temporal_data& lhs, const temporal_data& rhs)
    {
        return lhs.time_point_ >= rhs.time_point_;
    }

private:
    data_type        data_;
    time_point_type  time_point_;
}; 

}

#endif
