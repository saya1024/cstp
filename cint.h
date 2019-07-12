#pragma once

#include "cstring.h"
#include <type_traits>

namespace cstp
{

using uint = std::uint64_t;
using sint = std::int64_t;

template<class T>
inline constexpr int get_digit(T n)
{
    return n < 10 ? 1 : 1 + get_digit(n / 10);
}

inline constexpr int is_neg(sint n)
{
    return n < 0;
}

template<uint N, int D>
struct uint_to_cstr
{
    const cstring<D> str = uint_to_cstr<N / 10, D - 1>().str + to_cstr(N % 10 + '0');
};

template<uint N>
struct uint_to_cstr<N, 1>
{
    const cstring<1> str = N % 10 + '0';
};

template<uint N>
class cuint
{
public:
    constexpr cuint() :
        val_(N)
    {
    }

    constexpr cstring<get_digit(N)> cstr() const
    {
        return uint_to_cstr<N, get_digit(N)>().str;
    }

    constexpr uint value() const
    {
        return val_;
    }

private:
    uint val_;
};

template<sint N, bool Neg>
class _csint_basic
{
public:
    constexpr _csint_basic() :
        val_(N)
    {
    }

    constexpr sint value() const
    {
        return val_;
    }

private:
    sint val_;
};

template<sint N, bool Neg>
class _csint : public _csint_basic<N, Neg>
{
public:
    constexpr cstring<get_digit(-N) + 1> cstr() const
    {
        return '-' + uint_to_cstr<-N, get_digit(-N)>().str;
    }
};

template<sint N>
class _csint<N, false> : public _csint_basic<N, false>
{
public:
    constexpr cstring<get_digit(N)> cstr() const
    {
        return cuint<N>().cstr();
    }
};

template<sint N>
class csint : public _csint<N, is_neg(N)>
{
};

} // namespace cstp