#ifndef LIST_CONCEPTS_H
#define LIST_CONCEPTS_H

#include <concepts>
#include <compare>

template <typename From, typename To>
concept Convertible = std::convertible_to<From, To>;

template <typename T>
concept CopyMoveAssignable = 
    std::copy_constructible<T> && 
    std::move_constructible<T> && 
    std::assignable_from<T&, T>;

template<typename T, typename U>
concept EqualityComparable = std::equality_comparable_with<T, U>;

template <typename It>
concept InputIterator = std::input_iterator<It>; 

template <typename C>
concept CopyConstructible = requires(const C& c) {
    { C(c) } -> std::same_as<C>;
};

template <typename R>
concept Ranges = std::ranges::input_range<R>;

template <typename C>
concept Container = CopyConstructible<C> && std::move_constructible<C> && std::destructible<C> && requires(C c)
{
    typename C::value_type;
    typename C::reference;
    typename C::const_reference;
    typename C::iterator;
    typename C::const_iterator;
    typename C::difference_type;
    typename C::size_type;

    { c.begin() } noexcept -> std::same_as<typename C::iterator>;
    { c.end() } noexcept -> std::same_as<typename C::iterator>;
    
    { c.cbegin() } noexcept -> std::same_as<typename C::const_iterator>;
    { c.cend() } noexcept -> std::same_as<typename C::const_iterator>;

    { c.size() } noexcept -> std::same_as<typename C::size_type>;
    { c.empty() } noexcept -> std::same_as<bool>;
};

template <typename R, typename T>
concept ConvertibleRange = Ranges<R> && Convertible<std::ranges::range_value_t<R>, T>;

template <typename R, typename T>
concept PureRange = ConvertibleRange<R, T> && !Container<R>;

template <typename C, typename T>
concept ConvertibleContainer = Container<C> && Convertible<typename C::value_type, T>;

template <typename It, typename T>
concept ConvertibleInputIterator = 
    InputIterator<It> && 
    Convertible<typename It::value_type, T>;

template <typename S, typename It>
concept Sentinel = std::sentinel_for<S, It>;

#endif