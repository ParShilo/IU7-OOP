#include "iterator.h"

#pragma region Iterator
template <CopyMoveAssignable T>
Iterator<T>::Iterator() noexcept = default;

template <CopyMoveAssignable T>
Iterator<T>::Iterator(const Iterator& other) noexcept 
{
    this->ptr = other.ptr;
}

template <CopyMoveAssignable T>
Iterator<T>::Iterator(Iterator&& other) noexcept 
{
    this->ptr = std::move(other.ptr);
    other.ptr.reset();
};

template <CopyMoveAssignable T>
Iterator<T>::Iterator(const std::shared_ptr<typename List<T>::Node>& nodePtr) noexcept
{
    this->ptr = nodePtr;
};

#pragma endregion

template <CopyMoveAssignable T>
Iterator<T>& Iterator<T>::operator=(Iterator&& other) & noexcept 
{
    this->ptr = other.ptr;
    other.ptr.reset();
    return *this;
};

template <CopyMoveAssignable T>
Iterator<T>& Iterator<T>::operator=(const Iterator& other) & noexcept
{
    this->ptr = other.ptr;
    return *this;
};

template <CopyMoveAssignable T>
typename Iterator<T>::reference Iterator<T>::operator*() const 
{
    validate_ptr();
    return (this->ptr.lock()->get_value());
}

template <CopyMoveAssignable T>
typename Iterator<T>::pointer Iterator<T>::operator->() const 
{
    validate_ptr();
    return std::make_shared<T>(this->ptr.lock()->get_value());
}

template <CopyMoveAssignable T>
Iterator<T>& Iterator<T>::operator++() noexcept
{
    if (this->ptr.expired())
        return *this;
    this->ptr = this->ptr.lock()->get_next();
    return *this;
}

template <CopyMoveAssignable T>
Iterator<T> Iterator<T>::operator++(int) noexcept
{
    if (this->ptr.expired())
        return *this;
    Iterator copy(*this);
    this->ptr = this->ptr.lock()->get_next();
    return copy;
}

template <CopyMoveAssignable T>
bool Iterator<T>::operator==(const Iterator<T>& other) const noexcept 
{
    return this->ptr.lock() == other.ptr.lock();
}

template <CopyMoveAssignable T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const noexcept 
{
    return this->ptr.lock() != other.ptr.lock();
}

template <CopyMoveAssignable T>
void Iterator<T>::validate_ptr() const 
{
    if (!this->ptr.lock())
        throw IteratorException(__FILE__, typeid(Iterator<T>).name(), __FUNCTION__);
};