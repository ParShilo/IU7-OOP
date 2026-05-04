#include "base_iterator.h"

template <CopyMoveAssignable T>
BaseIterator<T>::operator bool() const noexcept
{
    return this->ptr.lock() && !this->ptr.expired();
}

template <CopyMoveAssignable T>
std::shared_ptr<typename List<T>::Node> BaseIterator<T>::get_node() const noexcept
{
    return this->ptr.lock();
}

template <CopyMoveAssignable T>
BaseIterator<T>::~BaseIterator() = default;