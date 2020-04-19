#ifndef ZMAN_TEMPORAL_ATTRIBUTES_HPP
#define ZMAN_TEMPORAL_ATTRIBUTES_HPP

#include <unordered_map>

namespace zman {

template<class KEY, class TIMELINE, class CONTAINER = std::unordered_map<KEY, TIMELINE>>
class temporal_attributes
{
public:
    using key_type        = KEY;
    using time_line_type  = TIMELINE;
    using container_type  = CONTAINER;
    using time_point_type = typename time_line_type::time_point_type;
    using value_type      = typename time_line_type::value_type;

    temporal_attributes() = default;

    void set_value_from(
          const time_point_type& from
        , const key_type&        key 
        , const value_type&      value
    )
    {
        auto& time_line = attributes_[key];
        time_line.insert(from, value);
    }

    void set_value_to(
          const time_point_type& to
        , const key_type&        key 
    )
    {
        auto& time_line = attributes_[key];
        time_line.insert(to);
    }

    const value_type* get_value(
          const time_point_type& time_point
        , const key_type&        key 
    ) const
    {
        auto it = attributes_.find(key); 
        if (it == attributes_.end()) return nullptr;
        
        const auto& time_line = it->second;
        return time_line.find(time_point);
    }

private:
    container_type attributes_;
}; 

}

#endif
