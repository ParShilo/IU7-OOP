#ifndef NODE_HPP
#define NODE_HPP

#include "list.h"
#include <iostream>

template <CopyMoveAssignable T>
class List;

template <CopyMoveAssignable T>
List<T>::Node::Node(std::shared_ptr<Node> next_node, const_reference value) noexcept(std::is_nothrow_copy_constructible_v<T>)
    : value(value)
    , next(std::move(next_node))
{}

template <CopyMoveAssignable T>
List<T>::Node::Node(std::shared_ptr<Node> next_node, value_type&& value) noexcept(std::is_nothrow_move_constructible_v<T>)
    : value(std::move(value))
    , next(std::move(next_node))
{}

template <CopyMoveAssignable T>
List<T>::Node::Node(const_reference value) noexcept(std::is_nothrow_copy_constructible_v<T>)
    : Node(nullptr, value)
{}

template <CopyMoveAssignable T>
List<T>::Node::Node(value_type&& value) noexcept(std::is_nothrow_move_constructible_v<T>)
    : Node(nullptr, std::move(value))
{}

template<CopyMoveAssignable T>
bool List<T>::Node::operator==(const Node &other) const noexcept
{
    return value == other.value;
}

template<CopyMoveAssignable T>
bool List<T>::Node::operator!=(const Node &other) const noexcept
{
    return value != other.value;
}

template<CopyMoveAssignable T>
void List<T>::Node::set_next(std::shared_ptr<Node> other) noexcept
{
    next = other;
}

template<CopyMoveAssignable T>
std::shared_ptr<typename List<T>::Node> List<T>::Node::get_next() const noexcept
{
    return next;
}

template<CopyMoveAssignable T>
T &List<T>::Node::get_value() noexcept
{
    return value;
}

template<CopyMoveAssignable T>
const T &List<T>::Node::get_value() const noexcept
{
    return value;
}

#endif