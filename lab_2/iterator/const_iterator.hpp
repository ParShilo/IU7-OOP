#include "const_iterator.h"

#pragma region ConstIterator
template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator() noexcept = default;

template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator(const ConstIterator& other) noexcept
{
    this->ptr = other.ptr;
}

template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator(const Iterator<T>& other) noexcept
{
    this->ptr = other.ptr;
}

template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator(ConstIterator&& other) noexcept 
{
    this->ptr = std::move(other.ptr.lock());
    other.ptr.reset();
}

template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator(Iterator<T>&& other) noexcept 
{
    this->ptr = std::move(other.ptr);
    other.ptr.reset();
}

template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<typename List<T>::Node>& nodePtr) noexcept 
{
    this->ptr = nodePtr;
}

#pragma endregion

template <CopyMoveAssignable T>
ConstIterator<T>& ConstIterator<T>::operator=(const ConstIterator& other) noexcept 
{
    this->ptr = other.ptr;
    return *this;
};

template <CopyMoveAssignable T>
ConstIterator<T>& ConstIterator<T>::operator=(ConstIterator&& other) noexcept 
{
    this->ptr = std::move(other.ptr);
    other.ptr.reset();
    return *this;
}

template <CopyMoveAssignable T>
typename ConstIterator<T>::reference ConstIterator<T>::operator*() const 
{
    validate_ptr();
    return this->ptr.lock()->get_value();
}

template <CopyMoveAssignable T>
typename ConstIterator<T>::pointer ConstIterator<T>::operator->() const 
{
    validate_ptr();
    return std::make_shared<T>(this->ptr.lock()->get_value());
}

template <CopyMoveAssignable T>
ConstIterator<T>& ConstIterator<T>::operator++() noexcept
{
    if (this->ptr.expired())
        return *this;
    this->ptr = this->ptr.lock()->get_next();
    return *this;
}

template <CopyMoveAssignable T>
ConstIterator<T> ConstIterator<T>::operator++(int) noexcept
{
    if (this->ptr.expired())
        return *this;
    ConstIterator copy(*this);
    this->ptr = this->ptr.lock()->get_next();
    return copy;
}

template <CopyMoveAssignable T>
bool ConstIterator<T>::operator==(const ConstIterator<T>& other) const noexcept 
{
    return this->ptr.lock() == other.ptr.lock();
}

template <CopyMoveAssignable T>
bool ConstIterator<T>::operator!=(const ConstIterator<T>& other) const noexcept 
{
    return this->ptr.lock() != other.ptr.lock();
}

template <CopyMoveAssignable T>
void ConstIterator<T>::validate_ptr() const 
{
    if (!this->ptr.lock())
        throw IteratorException(__FILE__, typeid(ConstIterator<T>).name(), __FUNCTION__);
};
