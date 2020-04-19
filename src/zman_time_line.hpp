#ifndef ZMAN_TIME_LINE_HPP
#define ZMAN_TIME_LINE_HPP

#include "zman_temporal_value.hpp"
#include <vector>
#include <algorithm>
#include <optional>
#include <stdexcept>

namespace zman {

template<
      class TIME_POINT
    , class VALUE
    , class CONTAINER = std::vector<temporal_value<TIME_POINT, std::optional<VALUE>>>
>
class time_line
{
public:
    using time_point_type     = TIME_POINT;
    using value_type          = VALUE;
    using container_type      = CONTAINER;
    using temporal_value_type = typename container_type::value_type;
    using optional_value_type = typename temporal_value_type::value_type;

    time_line() = default;

    void insert(
          const time_point_type& from
        , const value_type&      value
    )
    {
        insert(temporal_value_type(from, value));
    }

    void insert(const time_point_type& to)
    {
        insert(temporal_value_type(to, optional_value_type()));
    }
    
    const value_type* find(const time_point_type& time_point) const
    {
        bool no_values = values.empty();
        if (no_values) return nullptr;

        temporal_value_type tvalue(time_point, value_type{}); 
        auto it = std::lower_bound(begin(values), end(values), tvalue);

        bool exact_match = it != end(values) && it->time_point() == time_point;
        if (exact_match) return get_ptr_or_null(it->value());

        if (begin(values) == it) return nullptr;

        auto before = it - 1; 
        if (before->time_point() <= time_point) return get_ptr_or_null(before->value());

        return nullptr;
    }

    const container_type& content() 
    {
        return values;
    } 

private:
    void insert(temporal_value_type&& temporal_value)
    {
        if (try_add_when_no_values( std::move(temporal_value) ))    return;
        if (try_add_when_single_value( std::move(temporal_value) )) return;

        auto it = std::lower_bound(begin(values), end(values), temporal_value);
        if (try_add_at_the_end(it, std::move(temporal_value) )) return;

        validate_duplicate_time_point(temporal_value.time_point(), it->time_point()); 
        
        auto insert_before_it 
             = temporal_value.time_point() < it->time_point() 
             ? it
             : it + 1; 
        
        values.emplace(insert_before_it, std::move(temporal_value));
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

    bool try_add_when_no_values(temporal_value_type&& temporal_value) 
    {
        bool no_values = values.empty();
        if (no_values) values.emplace_back(temporal_value);
        return no_values;
    }

    bool try_add_when_single_value(temporal_value_type&& temporal_value)
    {
        bool single_value = values.size() == 1;
        if (single_value)
        {
            auto& value = values.front();
            validate_duplicate_time_point(temporal_value.time_point(), value.time_point());
            bool insert_before = value.time_point() > temporal_value.time_point();
            if (insert_before) values.emplace(begin(values), std::move(temporal_value)); 
            else               values.emplace_back(std::move(temporal_value)); 
        }
        return single_value;
    }

    template<class IT>
    bool try_add_at_the_end(IT it, temporal_value_type&& temporal_value)
    {
        bool at_the_end = it == end(values);
        if (at_the_end) values.emplace_back(std::move(temporal_value));
        return at_the_end;
    }   

    static const value_type* get_ptr_or_null(const optional_value_type& optional_value)
    {
        return optional_value ? &optional_value.value() : nullptr;
    }
       
    container_type values;
}; 

}

#endif
