#pragma once

#include "cstring.h"

namespace cstp
{

namespace detail
{

template<typename _Tp>
constexpr bool negative(_Tp num)
{
    return num < 0;
}

template<typename _Tp>
constexpr size_t digit(_Tp num)
{
    return num < 10 ? 1 : digit(num / 10) + 1;
}

template<typename _Tp>
constexpr _Tp abs(_Tp num)
{
    return negative(num) ? -num : num;
}

template<typename _Tp>
constexpr size_t caculate_size(_Tp num)
{
    return digit(abs(num)) + (negative(num) ? 2 : 1);
}

template<typename _Tp, _Tp _Num, size_t _Digit>
struct positive_number
{
    const cstring<_Digit + 1> cs = positive_number<_Tp, _Num / 10, _Digit - 1>().cs + to_cstr(_Num % 10 + '0');
};

template<typename _Tp, _Tp _Num>
struct positive_number<_Tp, _Num, 1>
{
    const cstring<2> cs = to_cstr(_Num % 10 + '0');
};

template<typename _Tp, _Tp _Num, bool _Negative>
struct cnumber
{
public:
    constexpr cstring<digit(-_Num) + 2> cstr() const
    {
        return "-" + positive_number<_Tp, -_Num, digit(-_Num)>().cs;
    }
};

template<typename _Tp, _Tp _Num>
struct cnumber<_Tp, _Num, false>
{
    constexpr cstring<digit(_Num) + 1> cstr() const
    {
        return positive_number<_Tp, _Num, digit(_Num)>().cs;
    }
};

}// namespace detail

template<std::int64_t _Num>
constexpr cstring<detail::caculate_size(_Num)> to_cstr()
{
    return detail::cnumber<std::int64_t, _Num, detail::negative(_Num)>().cstr();
}

template<std::uint64_t _Num>
constexpr cstring<detail::caculate_size(_Num)> uint64_to_cstr()
{
    return detail::cnumber<std::uint64_t, _Num, detail::negative(_Num)>().cstr();
}

} // namespace cstp