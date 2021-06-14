#ifndef ZMAN_DATE_TIME_HPP
#define ZMAN_DATE_TIME_HPP

#include <cstdint>

template<int64_t LARGEST_YEAR = 15'000'000'000>
class date_time
{
public:
    date_time()                                      = delete;
    date_time(date_time&&) noexcept                  = default;
    date_time(const date_time&&) noexcept            = default;
    date_time& operator=(date_time&&) noexcept       = default;
    date_time& operator=(const date_time&&) noexcept = default;

    date_time(
          int64_t year
        , int     month  = 1
        , int     day    = 1
        , int     hour   = 0
        , int     minute = 0
        , int     second = 0
    )
    {
        validate_year(year);
        validate_month(month);
        validate_day(day);
        validate_hour(hour);
        validate_minute(minute);
        validate_second(second);
        int_64_t encoded_value_
            = second 
            + seconds_in_minute * minute
            + seconds_in_hour   * hour
            + seconds_in_day    * day
            + seconds_in_month  * month
            + seconds_in_year   * std::abs(year)
        ;

    }

private:
    static constexpr int seconds_in_minute = 60;
    static constexpr int seconds_in_hour   = seconds_in_minute * 60;
    static constexpr int seconds_in_day    = seconds_in_hour   * 24; 
    static constexpr int seconds_in_month  = seconds_in_day    * 31; 
    static constexpr int seconds_in_year   = seconds_in_month  * 12; 
    int64_t encoded_value_;
};


#endif