#ifndef ZMAN_INVALID_DATA_HPP
#define ZMAN_INVALID_DATA_HPP

namespace zman {

template<class DATA>
struct invalid_data
{
    constexpr static DATA value = {}; 
};

template<class DATA>
bool is_valid_data(const DATA& data)
{
    return data != invalid_data<DATA>::value;
}

}

#endif
