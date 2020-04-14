#ifndef ZMAN_ID_HPP
#define ZMAN_ID_HPP

namespace zman {

template<class ID>
struct invalid_id
{
    constexpr static ID value = {}; 
};

template<class ID>
bool is_valid_id(const ID& id)
{
    return id != invalid_id<ID>::value;
}

}

#endif
