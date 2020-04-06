#pragma once

#include <cstdint>

namespace cstp
{

using size_t = std::size_t;

template<size_t...>
struct sequence
{
};

template<size_t _First , size_t... _Is>
struct generate_sequence :
    generate_sequence<_First - 1, _First - 1, _Is...>
{
};

template<size_t... _Is>
struct generate_sequence<0, _Is...> :
    sequence<_Is...>
{
};

} // namespace cstp