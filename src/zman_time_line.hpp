#ifndef ZMAN_TIME_LINE_HPP
#define ZMAN_TIME_LINE_HPP

namespace zman {

template<class TIME_POINT>
class time_line
{
public:
    using time_point = TIME_POINT;

    time_line() = default;

    time_line(time_point from_)
    :   from(from_) 
    ,   to(from)
    {
    }

    time_line(time_point from_, time_point to_)
    :   from(from_) 
    ,   to(to_)
    {
    }
    
    bool is_current()
    {
        return from == to;
    }

    time_point from_time_point()
    {
        return from;
    }

    time_point to_time_point()
    {
        return to;
    }

private:
    time_point from;
    time_point to;
}; 

}

#endif
