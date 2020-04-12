#ifndef ZMAN_TIME_LINE_HPP
#define ZMAN_TIME_LINE_HPP

#include "zman_temporal_id.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace zman {

template<class TEMPORAL_ID, class CONTAINER = std::vector<TEMPORAL_ID>>
class time_line
{
public:
    using temporal_id_type = TEMPORAL_ID;
    using time_point_type  = typename TEMPORAL_ID::time_point_type;
    using id_type          = typename TEMPORAL_ID::id_type;
    using container        = CONTAINER;

    time_line() = default;
    
    void add_id(
          const id_type&          id
        , const time_point_type&  time_point_from
    )
    {
        validate_id(id);

        if (try_add_when_no_values(id, time_point_from))    return;
        if (try_add_when_single_value(id, time_point_from)) return;

        temporal_id_type tid(id, time_point_from); 
        auto it = std::lower_bound(begin(values), end(values), tid);
        if (try_add_at_the_end(it, tid)) return;

        validate_duplicate_time_point(time_point_from, it->time_point()); 
        
        auto insert_before_it 
             = time_point_from < it->time_point() 
             ? it
             : it + 1; 
        
        values.insert(insert_before_it, tid);
    }

    void add_id(
          const id_type&          id
        , const time_point_type&  time_point_from
        , const time_point_type&  time_point_to
    );

    temporal_id_type find_id(const time_point_type& tpoint);

    const container& content() 
    {
        return values;
    } 

private:
    void validate_id(const id_type& id)
    {
        if (invalid_id<id_type>::value == id)
        {
            throw std::invalid_argument("invalid id value");
        }
    }
    
    void validate_duplicate_time_point(
          const time_point_type& time_point_1
        , const time_point_type& time_point_2
    )
    {
        if (time_point_1 == time_point_2)
        {
            throw std::invalid_argument("duplicate timepoint");
        }
    }

    bool try_add_when_no_values(
          const id_type&          id
        , const time_point_type&  time_point_from
    )
    {
        bool no_values = values.empty();
        if (no_values) values.emplace_back(id, time_point_from);
        return no_values;
    }

    bool try_add_when_single_value(
          const id_type&          id
        , const time_point_type&  time_point_from
    )
    {
        bool single_value = values.size() == 1;
        if (single_value)
        {
            temporal_id tid(id, time_point_from);
            auto& value = values.front();
            validate_duplicate_time_point(time_point_from, value.time_point());
            bool insert_before = value.time_point() > time_point_from;
            if (insert_before) values.insert(values.begin(), tid); 
            else               values.push_back(tid); 
        }
        return single_value;
    }

    template<class IT>
    bool try_add_at_the_end(IT it, const temporal_id_type& tid)
    {
        bool at_the_end = it == end(values);
        if (at_the_end) values.push_back(tid);
        return at_the_end;
    }   
       
    container values;
}; 

}

#endif
