#pragma once

#include <type_traits>

namespace sidekick
{

//
// Specialize this class to enable bitwise operations on a specified enum
// to automatically convert into a bit_flags value. Additionally, define typedef 'type'
// to use a different type than std::underlying_type as underlying type.
//
template <typename T>
struct enable_bit_flags_for_enum
{
    using type = void; // define 'type' if something other than std::underlying_type is desired.
};

namespace detail
{

//
// Check if bit_flags are enabled for enum by checking if enable_bit_flags_for_enum<T>
// doesn't contain a 'disabled' typedef.
//
template <typename T, typename = void>
struct bit_flags_enabled
{
    inline static constexpr bool value = true;
};

template <typename T>
struct bit_flags_enabled<T, std::void_t<typename enable_bit_flags_for_enum<T>::disabled>>
{
    inline static constexpr bool value = false;
};

template <typename T>
inline static constexpr bool bit_flags_enabled_v = bit_flags_enabled<T>::value;

//
// Check if a specialization of enable_bit_flags_for_enum<T> containts a typedef 'type'
// and use this or fall back to std::underlying_type
//
template <typename T, typename = void>
struct bit_flags_underlying_type
{
    using type = ::std::underlying_type_t<T>;
};

template <typename T>
struct bit_flags_underlying_type<T, std::void_t<typename enable_bit_flags_for_enum<T>::type>>
{
    using type = typename enable_bit_flags_for_enum<T>::type;
};

template <typename T>
using bit_flags_underlying_type_t = typename bit_flags_underlying_type<T>::type;

} // namespace detail


//
// bit_flags
//
template <typename T, typename V = detail::bit_flags_underlying_type_t<T>>
struct bit_flags
{
    static_assert(std::is_enum_v<T>, "T must be enum");
    using value_type = V;

    constexpr
    bit_flags() noexcept
      : bits{0}
    {}

    constexpr
    bit_flags(T e) noexcept
      : bits{static_cast<value_type>(e)}
    {}

    constexpr
    explicit bit_flags(value_type v) noexcept
      : bits{v}
    {}

    constexpr
    bit_flags& operator|=(T rhs) noexcept
    {
        bits |= static_cast<value_type>(rhs);
        return *this;
    }

    constexpr
    bit_flags& operator&=(T rhs) noexcept
    {
        bits &= static_cast<value_type>(rhs);
        return *this;
    }

    constexpr
    bit_flags& operator^=(T rhs) noexcept
    {
        bits ^= static_cast<value_type>(rhs);
        return *this;
    }

    constexpr
    explicit operator bool() const noexcept
    {
        return bits != 0;
    }

    constexpr
    explicit operator T() const noexcept
    {
        return static_cast<T>(bits);
    }

    value_type bits;
};



//
// operator==
//
template <typename T, typename V>
constexpr
bool operator==(bit_flags<T, V> lhs, bit_flags<T, V> rhs) noexcept
{
    return lhs.bits == rhs.bits;
}

template <typename T, typename V>
constexpr
bool operator==(bit_flags<T, V> lhs, T rhs) noexcept
{
    return lhs.bits == static_cast<decltype(lhs.bits)>(rhs);
}

template <typename T, typename V>
constexpr
bool operator==(T lhs, bit_flags<T, V> rhs) noexcept
{
    return rhs.bits == static_cast<decltype(rhs.bits)>(lhs);
}

//
// operator!=
//
template <typename T, typename V>
constexpr
bool operator!=(bit_flags<T, V> lhs, bit_flags<T, V> rhs) noexcept
{
    return lhs.bits != rhs.bits;
}

template <typename T, typename V>
constexpr
bool operator!=(bit_flags<T, V> lhs, T rhs) noexcept
{
    return !(lhs == rhs);
}

template <typename T, typename V>
constexpr
bool operator!=(T lhs, bit_flags<T, V> rhs) noexcept
{
    return !(lhs == rhs);
}

//
// operator|
//
template <typename T, typename V>
constexpr
bit_flags<T, V> operator|(bit_flags<T, V> lhs, bit_flags<T, V> rhs) noexcept
{
    return bit_flags<T, V>{lhs.bits | rhs.bits};
}

template <typename T, typename V>
constexpr
bit_flags<T, V> operator|(bit_flags<T, V> lhs, T rhs) noexcept
{
    return bit_flags<T, V>{lhs.bits | static_cast<V>(rhs)};
}

template <typename T, typename V>
constexpr
bit_flags<T, V> operator|(T lhs, bit_flags<T, V> rhs) noexcept
{
    return bit_flags<T, V>{static_cast<V>(lhs) | rhs.bits};
}

//
// operator&
//
template <typename T, typename V>
constexpr
bit_flags<T, V> operator&(bit_flags<T, V> lhs, bit_flags<T, V> rhs) noexcept
{
    return bit_flags<T, V>{lhs.bits & rhs.bits};
}

template <typename T, typename V>
constexpr
bit_flags<T, V> operator&(bit_flags<T, V> lhs, T rhs) noexcept
{
    return bit_flags<T, V>{lhs.bits & static_cast<V>(rhs)};
}

template <typename T, typename V>
constexpr
bit_flags<T, V> operator&(T lhs, bit_flags<T, V> rhs) noexcept
{
    return bit_flags<T, V>{static_cast<V>(lhs) & rhs.bits};
}

//
// operator^
//
template <typename T, typename V>
constexpr
bit_flags<T, V> operator^(bit_flags<T, V> lhs, bit_flags<T, V> rhs) noexcept
{
    return bit_flags<T, V>{lhs.bits ^ rhs.bits};
}

template <typename T, typename V>
constexpr
bit_flags<T, V> operator^(bit_flags<T, V> lhs, T rhs) noexcept
{
    return bit_flags<T, V>{lhs.bits ^ static_cast<V>(rhs)};
}

template <typename T, typename V>
constexpr
bit_flags<T, V> operator^(T lhs, bit_flags<T, V> rhs) noexcept
{
    return bit_flags<T, V>{static_cast<V>(lhs) ^ rhs.bits};
}

//
// Unary operators
//
template <typename T, typename V>
constexpr
bool operator!(bit_flags<T, V> flags) noexcept
{
    return flags.bits == 0;
}


} // namespace sidekick

//
// Bitwise operations result in bit_flags
//

template <typename T>
constexpr
std::enable_if_t<sidekick::detail::bit_flags_enabled_v<T>,
                 sidekick::bit_flags<T>>
operator|(T lhs, T rhs) noexcept
{
    return sidekick::bit_flags<T>{lhs} | rhs;
}

template <typename T>
constexpr
std::enable_if_t<sidekick::detail::bit_flags_enabled_v<T>,
                 sidekick::bit_flags<T>>
operator&(T lhs, T rhs) noexcept
{
    return sidekick::bit_flags<T>{lhs} & rhs;
}

template <typename T>
constexpr
std::enable_if_t<sidekick::detail::bit_flags_enabled_v<T>,
                 sidekick::bit_flags<T>>
operator^(T lhs, T rhs) noexcept
{
    return sidekick::bit_flags<T>{lhs} ^ rhs;
}

