#ifndef ZMAN_TEMPORAL_ATTRIBUTES_HPP
#define ZMAN_TEMPORAL_ATTRIBUTES_HPP

#include <unordered_map>

namespace zman {

template<class TIMELINE, class KEY, class CONTAINER = std::unordered_map<KEY> >
class temporal_attributes
{
public:
    using time_line_type  = TIMELINE;
    using value_type      = typename time_line_type::data_type;
    using time_point_type = typename time_line_type::time_point;
    using key_type        = KEY;
    using container_type  = CONTAINER;

    temporal_attributes() = default;

    void add_attribute(
          const time_point_type&  time_point
        , const key_type&         key 
        , const value_type&       value
    );

    const value_type& find_attribute(
          const time_point_type&  time_point
        , const key_type&         key 
    );

private:
    container_type attributes_;
}; 

}

#endif
