#ifndef ITERATOR_H
#define ITERATOR_H

#include "base_iterator.h"
#include "const_iterator.h"

template <CopyMoveAssignable T>
class List;

template <CopyMoveAssignable T>
class Iterator : public BaseIterator<T> 
{
public:
    friend class ConstIterator<T>;
    
    using pointer = std::shared_ptr<T>;
    using reference = T&;

    #pragma region Iterator
    Iterator() noexcept;
    Iterator(const Iterator& other) noexcept;
    Iterator(Iterator&& other) noexcept;
    explicit Iterator(const std::shared_ptr<typename List<T>::Node>& nodePtr) noexcept;
    #pragma endregion

    Iterator &operator=(const Iterator&) & noexcept;
    Iterator &operator=(Iterator&&) & noexcept;

    reference operator*() const;
    pointer operator->() const;

    Iterator& operator++() noexcept;
    Iterator operator++(int) noexcept;

    bool operator==(const Iterator<T>& other) const noexcept;

    void validate_ptr() const;

    ~Iterator() = default;
};

#include "iterator.hpp"

#endif