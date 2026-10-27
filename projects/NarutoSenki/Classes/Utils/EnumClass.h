#pragma once
#include <type_traits>

// NOTE: Enabled bit mask operators for all integer types enums

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T>
operator~(T a) noexcept
{
	using _MyBase = std::underlying_type_t<T>;
	return static_cast<T>(~static_cast<_MyBase>(a));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_integral_v<std::underlying_type_t<T>>, T>
operator|(T a, T b) noexcept
{
	using _MyBase = std::underlying_type_t<T>;
	return static_cast<T>(static_cast<_MyBase>(a) | static_cast<_MyBase>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T>
operator&(T a, T b) noexcept
{
	using _MyBase = std::underlying_type_t<T>;
	return static_cast<T>(static_cast<_MyBase>(a) & static_cast<_MyBase>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T>
operator^(T a, T b) noexcept
{
	using _MyBase = std::underlying_type_t<T>;
	return static_cast<T>(static_cast<_MyBase>(a) ^ static_cast<_MyBase>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T &>
operator|=(T &a, T b) noexcept
{
	using _MyBase = std::underlying_type_t<T>;
	return reinterpret_cast<T &>(reinterpret_cast<_MyBase &>(a) |= static_cast<_MyBase>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T &>
operator&=(T &a, T b) noexcept
{
	using _MyBase = std::underlying_type_t<T>;
	return reinterpret_cast<T &>(reinterpret_cast<_MyBase &>(a) &= static_cast<_MyBase>(b));
}

template <typename T>
inline constexpr std::enable_if_t<std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>, T &>
operator^=(T &a, T b) noexcept
{
	using _MyBase = std::underlying_type_t<T>;
	return reinterpret_cast<T &>(reinterpret_cast<_MyBase &>(a) ^= static_cast<_MyBase>(b));
}
