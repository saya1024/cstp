#pragma once

#include <type_traits>

namespace cstp
{

template<typename... Ts>
struct is_all_same :
    std::false_type
{
};

template<typename T>
struct is_all_same<T> :
    std::true_type
{
};

template<typename T, typename... Ts>
struct is_all_same<T, T, Ts...> :
    is_all_same<T, Ts...>
{
};

} // namespace cstp