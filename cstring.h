#pragma once

#include "sequence.h"
#include "traits.h"
#include <initializer_list>
#include <cstdint>

namespace cstp
{

template<int N>
class cstring
{
public:
    using const_pointer = const char*;
    using size_type = const std::size_t;

    template<int... Is>
    constexpr cstring(const_pointer ptr, sequence<Is...>) :
        elems_{ ptr[Is]... }
    {
    }

    constexpr cstring(char c) :
        elems_{ c }
    {
    }

    template<class... Ts>
    constexpr cstring(char c, Ts... args) :
        cstring<sizeof...(Ts) + 1>(cstring<1>(c) + cstring<sizeof...(Ts)>(args...))
    {
        static_assert(is_all_same<char, std::decay<Ts>::type...>::value, "all args should be const char");
    }

    template<int M>
    constexpr cstring(cstring<M>& cs) :
        cstring<M>(cs.data(), generate_sequence<M>{})
    {
    }

    template<int M>
    constexpr cstring(const char(&arr)[M]) :
        cstring<M - 1>(arr, generate_sequence<M - 1>{})
    {
    }

    template<int M>
    constexpr cstring<N + M> operator+(const cstring<M> cs) const
    {
        return concat_(cs, generate_sequence<N>{}, generate_sequence<M>{});
    }

    template<int M>
    constexpr cstring<N + M - 1> operator+(const char(&arr)[M]) const
    {
        return *this + cstring<M - 1>(arr);
    }

    constexpr cstring<N + 1> operator+(char c) const
    {
        return *this + cstring<1>(c);
    }

    constexpr size_type size() const
    {
        return static_cast<size_type>(N);
    }

    constexpr const_pointer data() const
    {
        return elems_;
    }

private:
    const char elems_[N];

    template<int M, int... Is, int... Js>
    constexpr cstring<N + M> concat_(cstring<M> cs, sequence<Is...>, sequence<Js...>) const
    {
        const char temp[] = { elems_[Is]..., cs.data()[Js]... };
        return { temp, generate_sequence<N + M>{} };
    }
};

template<unsigned N>
inline constexpr cstring<N - 1>
to_cstr(const char(&arr)[N])
{
    return cstring<N - 1>(arr);
}

inline constexpr cstring<1>
to_cstr(char c)
{
    return c;
}

template<class... Ts>
inline constexpr cstring<sizeof...(Ts) + 1>
to_cstr(char c, Ts...  args)
{
    static_assert(is_all_same<char, std::decay<Ts>::type...>::value, "all args should be const char");
    return cstring<1>(c) + cstring<sizeof...(Ts)>(args...);
}

template<int N, int M>
inline constexpr cstring<N + M - 1>
operator+(const char(&arr)[M], cstring<N> cs)
{
    return to_cstr(arr) + cs;
}

template<int N>
inline constexpr cstring<N + 1>
operator+(char c, cstring<N> cs)
{
    return to_cstr(c) + cs;
}

} // namespace cstp