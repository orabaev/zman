#ifndef ZMAN_TIME_LINE_HPP
#define ZMAN_TIME_LINE_HPP

#include "zman_temporal_data.hpp"
#include "zman_invalid_data.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace zman {

template<class TEMPORAL_DATA, class CONTAINER = std::vector<TEMPORAL_DATA>>
class time_line
{
public:
    using temporal_data_type = TEMPORAL_DATA;
    using time_point_type    = typename TEMPORAL_DATA::time_point_type;
    using data_type          = typename TEMPORAL_DATA::data_type;
    using container          = CONTAINER;

    time_line() = default;

    static constexpr auto invalid_data()
    {
        return zman::invalid_data<data_type>::value;
    }   

    void add_data(
          const data_type&        data
        , const time_point_type&  from
    )
    {
        if (try_add_when_no_values(data, from))    return;
        if (try_add_when_single_value(data, from)) return;

        temporal_data_type tdata(data, from); 
        auto it = std::lower_bound(begin(values), end(values), tdata);
        if (try_add_at_the_end(it, tdata)) return;

        validate_duplicate_time_point(from, it->time_point()); 
        
        auto insert_before_it 
             = from < it->time_point() 
             ? it
             : it + 1; 
        
        values.insert(insert_before_it, tdata);
    }
    
    data_type find_data(const time_point_type& time_point) const
    {
        bool no_values = values.empty();
        if (no_values) return invalid_data();

        temporal_data_type tdata(invalid_data(), time_point); 
        auto it = std::lower_bound(begin(values), end(values), tdata);
    
        bool exact_match = it != end(values) && it->time_point() == time_point;
        if (exact_match) return it->data(); 

        if (it == begin(values)) return invalid_data();

        auto before = it - 1; 
        return before->data();
    }

    const container& content() 
    {
        return values;
    } 

private:
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
          const data_type&        data
        , const time_point_type&  from
    )
    {
        bool no_values = values.empty();
        if (no_values) values.emplace_back(data, from);
        return no_values;
    }

    bool try_add_when_single_value(
          const data_type&        data
        , const time_point_type&  from
    )
    {
        bool single_value = values.size() == 1;
        if (single_value)
        {
            temporal_data tdata(data, from);
            auto& value = values.front();
            validate_duplicate_time_point(from, value.time_point());
            bool insert_before = value.time_point() > from;
            if (insert_before) values.insert(values.begin(), tdata); 
            else               values.push_back(tdata); 
        }
        return single_value;
    }

    template<class IT>
    bool try_add_at_the_end(IT it, const temporal_data_type& tdata)
    {
        bool at_the_end = it == end(values);
        if (at_the_end) values.push_back(tdata);
        return at_the_end;
    }   
       
    container values;
}; 

}

#endif
