#include "list.h"
#include <ranges>
#include <algorithm>
#include "../exception/exceptions.h"

#pragma region List

template <CopyMoveAssignable T>
List<T>::List(): head(nullptr), tail(nullptr) {}
template <CopyMoveAssignable T>
List<T>::List(const List<T>& list)
{
    push_back(list);
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>::List(const U* array, const size_t size)
{
    std::ranges::for_each(array, array + size, [this](const T& value) { push_back(value); });
}
template <CopyMoveAssignable T>
List<T>::List(List<T>&& list)
{
    len = list.len;
    head = std::move(list.head);
    tail = std::move(list.tail);

    list.len = 0;
}
template <CopyMoveAssignable T>
template<ConvertibleInputIterator<T> It, Sentinel<It> S>
List<T>::List(It beg, S end)  
{
    std::ranges::for_each(beg, end, [&](const T& value){push_back(value);});
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>::List(std::initializer_list<U> initializer_list)  
{
    std::ranges::for_each(initializer_list, [&](const T& value){push_back(value);});
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>::List(const size_t size, const U& value)  
{
    for (size_t i = 0; i < size; ++i) 
    {
        push_back(value);
    }
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
List<T>::List(const C& other) 
{
    push_back(other);
}
template <CopyMoveAssignable T>
template <PureRange <T> R>
List<T>::List(const R& range) 
{
    push_back(range);
}
template <CopyMoveAssignable T>
template <PureRange <T> R>
List<T>::List(R&& range)
{
    push_back(range);
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
List<T>::List(C&& other)
{
    push_back(other);
}

#pragma endregion




#pragma region =
template <CopyMoveAssignable T>
List<T>& List<T>::operator=(const List<T>& other) 
{
    clear();
    len = other.len;
    push_back(other);

    return *this;
} 
template <CopyMoveAssignable T>
List<T>& List<T>::operator=(List<T>&& other) 
{
    clear();
    len = std::move(other.len);
    head = std::move(other.head);
    tail = std::move(other.tail);

    other.len = 0;

    return *this;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>& List<T>::operator=(std::initializer_list<U> initializer_list)  
{
    clear();
    std::ranges::for_each(initializer_list, [&](const T& value){push_back(value);});
}
template <CopyMoveAssignable T>
template <PureRange<T> R>
List<T>& List<T>::operator=(const R& range)
{
    clear();
    std::ranges::for_each(range, [&](const T& value){push_back(value);});
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
List<T>& List<T>::operator=(const C& list)  
{
    clear();
    std::ranges::for_each(list, [&](const T& value){push_back(value);});
}

#pragma endregion





#pragma region push_back
template <CopyMoveAssignable T>
template <Convertible<T> U>
void List<T>::push_back(const U& value)
{
    std::shared_ptr<Node> new_node = allocate_node(value);
    if (!head) 
    {
        head = new_node;
        tail = new_node;
    }
    else 
    {
        tail->set_next(new_node);
        tail = new_node;
    }
    len++;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
void List<T>::push_back(U&& value) 
{
    std::shared_ptr<Node> new_node = allocate_node(std::forward<T>(value));

    if (!head) 
    {
        head = new_node;
        tail = new_node;
    }
    else 
    {
        tail->set_next(new_node);
        tail = new_node;
    }
    len++;
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
void List<T>::push_back(const C& list)
{ 
    std::ranges::for_each(list, [&] (const T& value) {push_back(value);});
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
void List<T>::push_back(C&& list) 
{
    std::ranges::for_each(std::move(list), [&] (T&& value) {push_back(std::move(value));});
}
template <CopyMoveAssignable T>
template <ConvertibleInputIterator<T> It>
void List<T>::push_back(It beg, It end) 
{
    for (auto it = beg; it < end; it++) 
        push_back(*it);
}
template <CopyMoveAssignable T>
template <PureRange<T> R>
void List<T>::push_back(const R& range)
{
    for (auto it: range)
        push_back(it);
}

#pragma endregion





#pragma region push_front
template <CopyMoveAssignable T>
template <Convertible<T> U>
void List<T>::push_front(const U& value) 
{
    std::shared_ptr<Node> new_node = allocate_node(value);

    if (!head) 
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        new_node->set_next(head);
        head = new_node;
    }
    len++;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
void List<T>::push_front(U&& value) 
{
    std::shared_ptr<Node> new_node = allocate_node(std::move(value));

    if (!head) 
    {
        head = new_node;
        tail = new_node;
    }
    else 
    {
        new_node->set_next(head);
        head = new_node;
    }
    len++;
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
void List<T>::push_front(const C& list)
{
    std::ranges::for_each(list, [&](const T& value) {push_front(value);});
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
void List<T>::push_front(C&& list) 
{
    std::ranges::for_each(std::move(list), [&](T&& value) {push_front(std::move(value));});
}
template <CopyMoveAssignable T>
template <ConvertibleInputIterator<T> It>
void List<T>::push_front(It beg, It end)
{
    for (auto it = beg; it < end; it++)
        push_front(*it);
}
template <CopyMoveAssignable T>
template<PureRange<T> R>
void List<T>::push_front(const R& range) 
{
    for (auto it: range)
        push_front(it);
}

#pragma endregion




#pragma region plus
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
List<T> List<T>::plus(const C& other) const 
{
    List<T> tmp(*this);
    tmp.push_back(other);
    return tmp;
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
List<T> List<T>::plus(C&& other) const 
{
    List<T> tmp(*this);
    tmp.push_back(other);
    return tmp;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T> List<T>::plus(const U& value) const 
{
    List<T> tmp(*this);
    tmp.push_back(value);
    return tmp;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T> List<T>::plus(U&& value) const 
{
    List<T> tmp(*this);
    tmp.push_back(std::forward<T>(value));
    return tmp;
}
template <CopyMoveAssignable T>
template<PureRange<T> R>
List<T> List<T>::plus(const R& range) const 
{
    List<T> tmp(*this);
    tmp.push_back(range);
    return tmp;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>& List<T>::operator+=(const U& value) 
{
    push_back(value);
    return *this;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>& List<T>::operator+=(U&& value) 
{
    push_back(std::move(value));
    return *this;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>& List<T>::operator+=(std::initializer_list<U> other) 
{
    std::ranges::for_each(other, [&](const T& value) {push_back(value);});
    return *this;
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
List<T>& List<T>::operator+=(const C& other) 
{
    std::ranges::for_each(other, [&](const T& value) {push_back(value);});
    return *this;
}
template <CopyMoveAssignable T>
template<PureRange<T> R>
List<T>& List<T>::operator+=(const R& range)
{
    std::ranges::for_each(range, [&](const T& value) {push_back(value);});
    return *this;
}

#pragma endregion




#pragma region insert_after
template <CopyMoveAssignable T> 
template <Convertible<T> U>
List<T>& List<T>::insert_after(const_iterator pos, const U& value) 
{
    if (!pos) 
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);

    auto new_node = allocate_node(value);
    new_node->set_next(pos.get_node()->get_next());
    pos.get_node()->set_next(new_node);
    ++len;
    return *this;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>& List<T>::insert_after(const_iterator pos, U&& value)
{
    if (!pos) 
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);

    auto new_node = allocate_node(std::move(value));
    new_node->set_next(pos.get_node()->get_next());
    pos.get_node()->set_next(new_node);
    ++len;
    return *this;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>& List<T>::insert_after(const_iterator pos, size_t count, const U& value)
{
    if (!pos)
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);
    
    if (count == 0)
        return *this;

    for (size_t i = 0; i < count; ++i)
    {
        insert_after(pos, value);
        pos++;
    }
    return *this;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>& List<T>::insert_after(const_iterator pos, size_t count, U&& value)
{    
    if (!pos)
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);
    if (count == 0)
        return *this;

    for (size_t i = 0; i < count; ++i)
    {
        insert_after(pos, std::forward<T>(value));
        pos++;
    }
    return *this;
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
List<T>& List<T>::insert_after(const_iterator pos, std::initializer_list<U> list)
{
    if (!pos) 
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);

    std::ranges::for_each(list, [&, this](const T& value)
    {
        insert_after(pos, value);
        pos++;
    });
    return *this;
}
template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
List<T>& List<T>::insert_after(const_iterator pos, const C& other) 
{
    if (!pos)
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);
    
    for (auto current = other.begin(); current != other.end(); ++current) 
    {
        insert_after(pos, *current);
        ++pos;
    }
    return *this;
}
template <CopyMoveAssignable T>
template<PureRange<T> R>
List<T>& List<T>::insert_after(const_iterator pos, const R& range) 
{
    if (!pos)
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);

    for (auto current : range) 
    {
        insert_after(pos, current);
        ++pos; 
    }
    return *this;
}
template <CopyMoveAssignable T>
template <ConvertibleInputIterator<T> It>
List<T>& List<T>::insert_after(const_iterator pos, It beg, It end) 
{
    if (!pos)
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);

    for (auto it = pos, current = beg; current != end; current++)
        insert_after(it, *current);
    
    return *this;
}

#pragma endregion




#pragma region pop
template <CopyMoveAssignable T>
void List<T>::pop_back() 
{
    check_null_list();

    if (len == 1) 
    {
        clear();
        return;
    }
    
    auto prev = head;
    while (prev->get_next() != tail)
        prev = prev->get_next();

    prev->set_next(nullptr);
    tail = prev;
    len--;
}
template <CopyMoveAssignable T>
void List<T>::pop_front()  
{
    check_null_list();

    if (len == 1) 
    {
        clear();
        return;
    }
    head = head->get_next();
    len--;
}

template <CopyMoveAssignable T>
List<T>& List<T>::erase(const_iterator pos) 
{
    if (!pos)
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);

    if (pos == begin()) 
    {
        pop_front();
        return *this;
    }
    auto i = begin();
    auto j = begin();
    j++;
    for (; i != end(), j != pos; i++, j++);
    if (j == end()) 
    {
        pop_back();
        return *this;
    }
    --len;
    link_nodes(i, i);
    pos.get_node()->set_next(nullptr);

    return *this;
}
template <CopyMoveAssignable T>
List<T>& List<T>::erase(const_iterator first, const_iterator last) 
{
    if (!first || !last)
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);

    if (first == last)
        return *this;

    size_t count = 0;
    auto it = first;
    while (it != last) 
    {
        ++count;
        ++it;
    }

    if (first == cbegin())
        head = last.get_node()->get_next();
    else 
    {
        auto i = begin();
        auto j = begin();
        j++;
        for (; j != first; j++, i++);
        if (last == cend()) 
        {
            tail = i.get_node();
            tail->set_next(nullptr);
        } 
        else
            link_nodes(i, last);
    }
    len -= count;
    return *this;
}
template <CopyMoveAssignable T>
List<T>& List<T>::erase(const_iterator beg, size_t size)
{
    if (size == 0)
        return *this;
    ConstIterator<T> end = beg;
    for (size_t i = 0; i < size - 1; i++, end++);
    erase(beg, end);

    len--;
    return *this;
}

template <CopyMoveAssignable T>
void List<T>::resize(const size_t count) 
{
    if (count == len) return;

    if (count < len) 
    {
        auto it = begin();
        for (size_t i = 1; i < count; ++i)
            ++it;

        auto node = it.get_node();
        node->set_next(nullptr);
        tail = node;
        len = count;
    } 
    else 
    {
        T default_value{};
        while (len < count)
            push_back(default_value);
    }
}
template <CopyMoveAssignable T>
template <Convertible<T> U>
void List<T>::resize(const size_t count, const U& value) 
{
    if (count < len)
        resize(count);
    else
        while (len < count)
            push_back(value);
}
#pragma endregion




#pragma region special_methods
template <CopyMoveAssignable T>
void List<T>::swap(List<T>& other) noexcept 
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(len, other.len);
}

template <CopyMoveAssignable T>
void List<T>::reverse() noexcept 
{
    std::shared_ptr<Node> prev = nullptr;
    std::shared_ptr<Node> current = head;
    std::shared_ptr<Node> next = nullptr;
    tail = head;
    
    while (current) 
    {
        next = current->get_next();
        current->set_next(prev);
        prev = current;
        current = next;
    }
    head = prev;
}

template <CopyMoveAssignable T>
int List<T>::unique() noexcept 
{
    if (empty())
        return 0;

    int amount_of_deleted = 0;
    auto current = begin();

    while (current && current.get_node()->get_next()) 
    {
        if (current.get_node()->get_value() == current.get_node()->get_next()->get_value()) 
        {
            link_nodes(current, ++ConstIterator<T>(current));
            --len;
            ++amount_of_deleted;
        } 
        else
            ++current;
    }

    if (head) 
    {
        auto it = begin();
        while (it.get_node()->get_next())
            ++it;
        tail = it.get_node();
    } 
    else
        tail = nullptr;

    return amount_of_deleted;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool List<T>::contains(const U& value) const noexcept 
{
    for (auto it = cbegin(); it != cend(); ++it)
        if (*it == value)
            return true;
        
    return false;
}

#pragma endregion




#pragma region iterators_methods
template <CopyMoveAssignable T>
List<T>::const_iterator List<T>::begin() const noexcept 
{
    return ConstIterator<T>(head);
}

template <CopyMoveAssignable T>
List<T>::const_iterator List<T>::end() const noexcept 
{
    return ConstIterator<T>(nullptr);
}

template <CopyMoveAssignable T>
List<T>::const_iterator List<T>::cbegin() const noexcept 
{
    return ConstIterator<T>(head);
}

template <CopyMoveAssignable T>
List<T>::const_iterator List<T>::cend() const noexcept 
{
    return ConstIterator<T>(nullptr);
}

template <CopyMoveAssignable T>
List<T>::iterator List<T>::begin() noexcept 
{
    return Iterator<T>(head);
}

template <CopyMoveAssignable T>
List<T>::iterator List<T>::end() noexcept 
{
    return Iterator<T>(nullptr);
}

#pragma endregion





#pragma region base_methods

template <CopyMoveAssignable T>
typename List<T>::size_type List<T>::size() const noexcept 
{
    return len;
}

template <CopyMoveAssignable T>
bool List<T>::empty() const noexcept 
{
    return len == 0;
}

template <CopyMoveAssignable T>
typename List<T>::reference List<T>::front() 
{
    check_null_list();
    return head->get_value();
}

template <CopyMoveAssignable T>
typename List<T>::reference List<T>::back() 
{
    check_null_list();
    return tail->get_value();
}

template <CopyMoveAssignable T>
typename List<T>::const_reference List<T>::front() const 
{
    check_null_list();
    return head->get_value();
}

template <CopyMoveAssignable T>
typename List<T>::const_reference List<T>::back() const 
{
    check_null_list();
    return tail->get_value();
}

template<CopyMoveAssignable T>
void List<T>::clear() noexcept 
{
    head = nullptr;
    tail = nullptr;
    len = 0;
}

#pragma endregion




#pragma region allocation_methods

template <CopyMoveAssignable T>
template <Convertible<T> U>
std::shared_ptr<typename List<T>::Node> List<T>::allocate_node(const U& data) const 
{
    std::shared_ptr<Node> new_node = nullptr;

    try 
    {
        new_node = std::make_shared<Node>(data);
    } 
    catch (std::bad_alloc& ex) 
    {
        throw MemoryException(__FILE__, typeid(List).name(), __FUNCTION__);
    }
    
    return new_node;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
std::shared_ptr<typename List<T>::Node> List<T>::allocate_node(U&& data) const 
{
    std::shared_ptr<Node> new_node = nullptr;

    try 
    {
        new_node = std::make_shared<Node>(std::move(data));
    } 
    catch (std::bad_alloc& ex) 
    {
        throw MemoryException(__FILE__, typeid(List).name(), __FUNCTION__);
    }

    return new_node;
}

#pragma endregion

template <CopyMoveAssignable T>
void List<T>::check_null_list() const 
{
    if (len == 0) 
    {
        throw EmptyListException(__FILE__, typeid(List).name(), __FUNCTION__);
    }
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool List<T>::operator==(const List<U>& other) const noexcept
{
    if (len != other.len)
        return false;
    for (auto i = begin(), j = other.begin(); i != end(), j != other.end(); i++, j++)
        if (*i != *j)
            return false;
    return true;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool List<T>::operator!=(const List<U>& other) const noexcept
{
    return !(*this == other);
}

template <CopyMoveAssignable T>
void List<T>::link_nodes(const_iterator from, const_iterator to) 
{
    if (!from || !to) 
    {
        throw TransmittedIteratorException(__FILE__, typeid(List).name(), __FUNCTION__);
    }
    from.get_node()->set_next(to.get_node()->get_next());
}

template <CopyMoveAssignable T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) 
{
    os << "{";

    auto it = list.cbegin();
    if (it != list.cend()) 
    {
        os << *it;
        ++it;
    }
    for (; it != list.cend(); ++it) 
        os << ", " << *it;

    os << "}";
    os << "(" << list.size() << ")";

    return os;
}

