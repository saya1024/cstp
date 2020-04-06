#pragma once

#include <cstdint>

namespace cstp
{

using size_t = std::size_t;

template<size_t _Sz>
struct cstring
{
    char data[_Sz];

    constexpr size_t size() const
    {
        return _Sz - 1;
    }

    const char* c_str() const
    {
        return data;
    }
};

template<size_t _Sz>
inline constexpr cstring<_Sz>
to_cstr(const char(&arr)[_Sz])
{
    cstring<_Sz> cs = { 0 };
    for (size_t i = 0; i < _Sz - 1; i++)
    {
        cs.data[i] = arr[i];
    }
    return cs;
}

inline constexpr cstring<2>
to_cstr(const char c)
{
    return { c, 0 };
}

template<size_t _Sz1, size_t _Sz2>
inline constexpr cstring<_Sz1 + _Sz2 - 1>
cstrcat(const char(&arr1)[_Sz1], const char(&arr2)[_Sz2])
{
    cstring<_Sz1 + _Sz2 - 1> cs = { 0 };
    for (size_t i = 0; i < _Sz1 - 1; i++)
    {
        cs.data[i] = arr1[i];
    }
    for (size_t i = 0; i < _Sz2 - 1; i++)
    {
        cs.data[i + _Sz1 - 1] = arr2[i];
    }
    return cs;
}

template<size_t _Sz1, size_t _Sz2>
inline constexpr cstring<_Sz1 + _Sz2 - 1>
operator+(const cstring<_Sz1> cs1, const cstring<_Sz2> cs2)
{
    return cstrcat(cs1.data, cs2.data);
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