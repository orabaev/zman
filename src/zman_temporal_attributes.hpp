#ifndef ZMAN_TEMPORAL_ATTRIBUTES_HPP
#define ZMAN_TEMPORAL_ATTRIBUTES_HPP

#include <unordered_map>

namespace zman {

template<class TIMELINE, class KEY, class CONTAINER = std::unordered_map<KEY, typename TIMELINE::data_type>>
class temporal_attributes
{
public:
    using time_line_type  = TIMELINE;
    using value_type      = typename time_line_type::data_type;
    using time_point_type = typename time_line_type::time_point_type;
    using key_type        = KEY;
    using container_type  = CONTAINER;

    temporal_attributes() = default;

    void add_attribute(
          const time_point_type&  time_point
        , const key_type&         key 
        , const value_type&       value
    )
    {
        auto& time_line = attributes_[key];
        time_point.add_data(value, time_point);
    }

    const value_type& find_attribute(
          const time_point_type&  time_point
        , const key_type&         key 
    ) const
    {
        auto it = attributes_.find(key); 
        if (it == attributes_.end()) return time_line_type::invalid_data();
        
        const auto& time_line = *it;
        return time_line.find_data(time_point);
    }

private:
    container_type attributes_;
}; 

}

#endif
