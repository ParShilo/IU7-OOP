#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H

#include <memory>
#include <iterator>
#include "list_concepts.h"

template <CopyMoveAssignable T>
class List;

template <CopyMoveAssignable T>
class BaseIterator 
{
public:
    using value_type = T;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    BaseIterator() = default;
    explicit operator bool() const noexcept;
    virtual ~BaseIterator() = 0;

protected:
    std::weak_ptr<typename List<T>::Node> ptr;
    std::shared_ptr<typename List<T>::Node> get_node() const noexcept;

    friend class List<T>;
};

#include "base_iterator.hpp"

#endif