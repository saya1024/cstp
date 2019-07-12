#pragma once

namespace cstp
{

template<int... Is>
struct sequence
{
};

template<int N, int... Is>
struct generate_sequence :
    generate_sequence<N - 1, N - 1, Is...>
{
};

template<int... Is>
struct generate_sequence<0, Is...> :
    sequence<Is...>
{
};

} // namespace cstp