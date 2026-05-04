#include <cassert>
#include <iostream>
#include <vector>
#include <ranges>

#include "./list/list.h"

void test_list()
{
    // Конструктор по умолчанию
    List<int> list;
    assert(list.empty());
    assert(list.size() == 0);

    // Добавление
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    assert(list.front() == 5);
    assert(list.back() == 20);
    assert(list.size() == 3);

    // Конструктор с initializer_list
    List<int> initList{1, 2, 3};
    assert(initList.size() == 3);
    auto it = initList.begin();
    assert(*it++ == 1);
    assert(*it++ == 2);
    assert(*it++ == 3);

    // Конструктор копирования
    List<int> copied(initList);
    assert(copied == initList);

    // Конструктор
    List<int> moved(std::move(initList));
    assert(moved.size() == 3);
    assert(initList.empty());

    // Присваивание переноса
    List<int> moveAssigned;
    moveAssigned = std::move(moved);
    assert(moveAssigned.size() == 3);

    // Перегрузка добавления элементов в конец
    List<int> combo;
    combo.push_back(1);
    combo.push_back(std::move(2));
    combo.push_back(copied);
    assert(combo.size() == 5);

    // Перегрузка добавления элементов в начало
    combo.push_front(100);
    combo.push_front(std::move(200));
    combo.push_front(copied);
    assert(combo.front() == 3);

    // Оператор +=
    combo += 300;
    combo += std::move(400);
    combo += copied;
    combo += {7, 8, 9};
    assert(combo.size() >= 15);

    // Вставка после
    auto pos = combo.begin();
    ++pos;
    combo.insert_after(pos, 777);
    combo.insert_after(pos, 2, 888);
    combo.insert_after(pos, {999, 1000});
    assert(combo.size() >= 20);

    // Удаление элемента
    size_t oldSize = combo.size();
    combo.erase(combo.begin());
    assert(combo.size() == oldSize - 1);

    // Обрезание списка
    combo.erase(combo.begin(), 3);
    assert(combo.size() == oldSize - 4);

    // Изменение размера
    combo.resize(5);
    assert(combo.size() == 5);
    combo.resize(10, 42);
    assert(combo.size() == 10);

    // Вывод начала и хвоста
    assert(combo.front() == combo.begin().operator*());
    assert(combo.back() == 42);

    // Переворот
    auto beforeReverse = combo.front();
    combo.reverse();
    assert(combo.back() == beforeReverse);

    // Удаление повторяющихся
    combo.push_back(42);
    combo.push_back(42);
    int removed = combo.unique();
    assert(removed >= 1);

    // Удаление хвоста и головы
    size_t s = combo.size();
    combo.pop_front();
    combo.pop_back();
    assert(combo.size() == s - 2);

    // Очистка
    combo.clear();
    assert(combo.empty());
    assert(combo.begin() == combo.end());

    // Смена
    List<int> a{1, 2, 3}, b{4, 5};
    a.swap(b);
    assert(a.size() == 2);
    assert(b.size() == 3);
    assert(a.front() == 4);
    assert(b.front() == 1);

    // Вхождение
    List<int> contains_list{1, 2, 3, 4, 5};
    assert(contains_list.contains(1));
    assert(contains_list.contains(3));
    assert(!contains_list.contains(0));
    assert(!contains_list.contains(99));

    // Операторы == и !=
    List<int> comp1{1, 2, 3}, comp2{1, 2, 3}, comp3{3, 2, 1};
    assert(comp1 == comp2);
    assert(comp1 != comp3);

    // Константный итератор
    const List<int> constList{10, 20, 30};
    auto cit = constList.cbegin();
    assert(*cit++ == 10);
    assert(*cit++ == 20);
    assert(*cit++ == 30);
    assert(cit == constList.cend());

    // Конструктор из массива
    int arr[] = {7, 8, 9};
    List<int> fromArray(arr, 3);
    assert(fromArray.size() == 3);
    assert(*fromArray.begin() == 7);

    // Конструктор заполнения
    List<int> filled(5, 99);
    for (auto val : filled) assert(val == 99);

    // Конструктор из вектора
    std::vector<int> vec{1, 2, 3, 4};
    List<int> fromVec(vec.begin(), vec.end());
    assert(fromVec.size() == 4);

    // Конструктор из range
    List<int> fromRange(std::ranges::views::iota(0, 5));
    int counter = 0;
    for (int val : fromRange) assert(val == counter++);

    // Оператор +
    List<int> base{1, 2};
    List<int> result = base.plus(3).plus(List<int>{4, 5});
    int expected[] = {1, 2, 3, 4, 5};
    int i = 0;
    for (int val : result) assert(val == expected[i++]);

    std::cout << "All tests passed!\n";
}

int main() {
    test_list();
    return 0;
}
