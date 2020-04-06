#pragma once

#include "sequence.h"

namespace cstp
{

template<size_t _Sz>
class cstring
{
public:
    using const_pointer = const char*;

    template<size_t... _Is>
    constexpr cstring(const_pointer ptr, sequence<_Is...>) :
        elems_{ ptr[_Is]... }
    {
    }

    template<size_t... _Is, size_t... _Js>
    constexpr cstring(const_pointer ptr1, const_pointer ptr2, sequence<_Is...>, sequence<_Js...>) :
        elems_{ ptr1[_Is]..., ptr2[_Js]... }
    {
    }

    constexpr size_t size() const
    {
        return _Sz - 1;
    }

    constexpr const_pointer c_str() const
    {
        return elems_;
    }

private:
    const char elems_[_Sz];
};

template<size_t _Sz>
inline constexpr cstring<_Sz>
to_cstr(const char(&arr)[_Sz])
{
    return { arr, generate_sequence<_Sz>{} };
}

inline constexpr cstring<2>
to_cstr(const char c)
{
    return { &c, generate_sequence<1>{} };
}

template<size_t _Sz1, size_t _Sz2>
inline constexpr cstring<_Sz1 + _Sz2 - 1>
cstrcat(const char(&arr1)[_Sz1], const char(&arr2)[_Sz2])
{
    return { arr1, arr2, generate_sequence<_Sz1 - 1>{}, generate_sequence<_Sz2>{} };
}

template<size_t _Sz1, size_t _Sz2>
inline constexpr cstring<_Sz1 + _Sz2 - 1>
operator+(const cstring<_Sz1> cs1, const cstring<_Sz2> cs2)
{
    return { cs1.c_str(), cs2.c_str(), generate_sequence<_Sz1 - 1>{}, generate_sequence<_Sz2>{} };
}

template<size_t _Sz1, size_t _Sz2>
inline constexpr cstring<_Sz1 + _Sz2 - 1>
operator+(const char(&arr)[_Sz1], const cstring<_Sz2> cs)
{
    return to_cstr(arr) + cs;
}

template<size_t _Sz1, size_t _Sz2>
inline constexpr cstring<_Sz1 + _Sz2 - 1>
operator+(const cstring<_Sz1> cs, const char(&arr)[_Sz2])
{
    return cs + to_cstr(arr);
}

} // namespace cstp