#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include "base_iterator.h"
#include "exceptions.h"

template <CopyMoveAssignable T>
class List;

template <CopyMoveAssignable T>
class Iterator;

template <CopyMoveAssignable T>
class ConstIterator : public BaseIterator<T> 
{
public:
    using pointer = const std::shared_ptr<T>;
    using reference = const T&;

    #pragma region ConstIterator
    ConstIterator() noexcept;
    ConstIterator(const ConstIterator& other) noexcept;
    ConstIterator(const Iterator<T>& other) noexcept;
    ConstIterator(ConstIterator&& other) noexcept;
    ConstIterator(Iterator<T>&& other) noexcept;
    explicit ConstIterator(const std::shared_ptr<typename List<T>::Node>& ptr) noexcept;
    #pragma endregion

    ConstIterator& operator=(const ConstIterator& other) noexcept;
    ConstIterator& operator=(ConstIterator&& other) noexcept;

    reference operator*() const;
    pointer operator->() const;

    ConstIterator& operator++() noexcept;
    ConstIterator operator++(int) noexcept;

    bool operator==(const ConstIterator<T>& other) const noexcept;
    bool operator!=(const ConstIterator<T>& other) const noexcept;

    void validate_ptr() const;

    ~ConstIterator() = default;
};

#include "const_iterator.hpp"

#endif