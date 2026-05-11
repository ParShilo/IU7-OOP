#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "base_list.h"
#include "list_concepts.h"
#include <initializer_list>
#include <memory>

#include "iterator.h"
#include "const_iterator.h"
#include "base_iterator.h"

template<CopyMoveAssignable T>
class List: public baseList
{
public:
#pragma region aliases
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = Iterator<T>;
    using const_iterator = ConstIterator<T>;
    using difference_type = ptrdiff_t;
    using size_type = size_t;
#pragma endregion


public:
    #pragma region List

    List() noexcept;

    explicit List(const List<T> &list);

    List(List<T> &&list);

    template<Convertible<T> U>
    explicit List(std::initializer_list<U> initializer_list);

    template<Convertible<T> U>
    List(const U *array, const size_t size);

    template <Convertible<T> U>
    List(const size_t size, const U& value);

    template<ConvertibleInputIterator<T> It, Sentinel<It> S>
    List(It beg, S end);

    template <ConvertibleContainer<T> C>
    explicit List(const C& other);

    template <PureRange <T> R>
    explicit List(const R& range);

    template <ConvertibleContainer<T> C>
    explicit List(C&& other);

    template <PureRange <T> R>
    explicit List(R&& range);

    #pragma endregion
    



    #pragma region =

    List<T> &operator=(const List<T> &list);

    List<T> &operator=(List<T> &&list);

    template<Convertible<T> U>
    List<T> &operator=(std::initializer_list<U> initializer_list);

    template <PureRange<T> R>
    List<T> &operator=(const R &range);

    template <ConvertibleContainer<T> C>
    List<T> &operator=(const C &list);

    ~List() = default;

    #pragma endregion




    #pragma region push_back

    template<Convertible<T> U>
    void push_back(const U &value);
    
    template<Convertible<T> U>
    void push_back(U &&value);
    
    template<ConvertibleContainer<T> C>
    void push_back(const C &other);
    
    template<ConvertibleContainer<T> C>
    void push_back(C &&other);
    
    template <ConvertibleInputIterator<T> It>
    void push_back(It beg, It end);

    template <PureRange<T> R>
    void push_back(const R& range);

    #pragma endregion




    #pragma region push_front

    template<Convertible<T> U>
    void push_front(const U &value);

    template<Convertible<T> U>
    void push_front(U &&value);

    template<ConvertibleContainer<T> C>
    void push_front(const C &other);

    template<ConvertibleContainer<T> C>
    void push_front(C &&other);

    template <ConvertibleInputIterator<T> It>
    void push_front(It beg, It end);

    template <PureRange<T> R>
    void push_front(const R& range);

    #pragma endregion




    #pragma region iterators_methods

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;

    #pragma endregion





    #pragma region +

    template <Convertible<T> U>
    List<T> operator+(const U& value) const;

    template <Convertible<T> U>
    List<T> operator+(U&& value) const;

    template <ConvertibleContainer<T> C>
    List<T> operator+(const C& other) const;

    template <ConvertibleContainer<T> C>
    List<T> operator+(C&& other) const;

    template <PureRange<T> R>
    List<T> operator+(const R& range) const;

    template <CopyMoveAssignable U, Convertible<U> V>
    friend List<U> operator+(const V& value, const List<U>& list);

    template <CopyMoveAssignable U, Convertible<U> V>
    friend List<U> operator+(V&& value, const List<U>& list);

    template<ConvertibleContainer<T> C>
    List<T> &operator+=(const C &other);

    template<PureRange<T> R>
    List<T> &operator+=(const R& range);

    template<Convertible<T> U>
    List<T> &operator+=(std::initializer_list<U> other);

    template<Convertible<T> U>
    List<T> &operator+=(const U &value);

    template<Convertible<T> U>
    List<T> &operator+=(U &&value);

    #pragma endregion




    #pragma region insert_after

    template<Convertible<T> U>
    List<T>& insert_after(const_iterator pos,  std::initializer_list<U> list);

    template<Convertible<T> U>
    List<T>& insert_after(const_iterator pos, size_t count, const U &value);

    template<Convertible<T> U>
    List<T>& insert_after(const_iterator pos, size_t count, U &&value);

    template<Convertible<T> U>
    List<T>& insert_after(const_iterator pos, const U &value);

    template<Convertible<T> U>
    List<T>& insert_after(const_iterator pos, U &&value);

    template <ConvertibleContainer<T> C>
    List<T>& insert_after(const_iterator pos, const C& other);

    template<PureRange<T> R>
    List<T>& insert_after(const_iterator pos, const R& range);

    template <ConvertibleInputIterator<T> It>
    List<T>& insert_after(const_iterator pos, It beg, It end);

    #pragma endregion





    #pragma region pop

    List<T>& erase(const_iterator pos);
    List<T>& erase(const_iterator first, const_iterator last);
    List<T>& erase(const_iterator beg, size_t size);
    void pop_back();
    void pop_front();

    #pragma endregion





    #pragma region special_methods

    void reverse() noexcept;
    int unique() noexcept;

    void resize(const size_t count);

    template<Convertible<T> U>
    void resize(const size_t count, const U &value);

    void swap(List<T> &other) noexcept;

    template <EqualityComparable<T> U>
    bool contains(const U& value) const noexcept;

    #pragma endregion




    #pragma region base_methods

    void clear() noexcept;

    size_type size() const noexcept override;
    bool empty() const noexcept override;


    reference front();
    reference back();

    const_reference front() const;
    const_reference back() const;

    #pragma endregion

    template <EqualityComparable<T> U>
    bool operator==(const List<U>& other) const noexcept;
    
    template <EqualityComparable<T> U>
    bool operator!=(const List<U>& other) const noexcept;

protected:
    #pragma region friends
    friend class Iterator<T>;
    friend class ConstIterator<T>;
    friend class BaseIterator<T>;
    #pragma endregion

    class Node
    {
    public:
        explicit Node(const T &value) noexcept(std::is_nothrow_copy_constructible_v<T>);
        explicit Node(T &&value) noexcept(std::is_nothrow_move_constructible_v<T>);
        Node(std::shared_ptr<Node> cur, T d);

        explicit Node(const Node &) noexcept;
        explicit Node(Node &&) noexcept;

        bool operator==(const Node &other) const noexcept;
        bool operator!=(const Node &other) const noexcept;

        void set_next(std::shared_ptr<Node> other) noexcept;
        std::shared_ptr<Node> get_next() const noexcept;

        T &get_value() noexcept;
        const T &get_value() const noexcept;

    private:
        T value;
        std::shared_ptr<Node> next;
    };


private:
    #pragma region allocation_methods
    template<Convertible<T> U>
    std::shared_ptr<Node> allocate_node(const U &data) const;
    template<Convertible<T> U>
    std::shared_ptr<Node> allocate_node(U &&data) const;
    #pragma endregion

    void check_null_list() const;
    void link_nodes(const_iterator from, const_iterator to);

private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
};

template<CopyMoveAssignable T>
std::ostream &operator<<(std::ostream &os, const List<T> &list);

template <CopyMoveAssignable U, Convertible<U> V>
List<U> operator+(const V& value, const List<U>& list);

template <CopyMoveAssignable U, Convertible<U> V>
List<U> operator+(V&& value, const List<U>& list);

#include "node.hpp"
#include "list.hpp"

#endif
