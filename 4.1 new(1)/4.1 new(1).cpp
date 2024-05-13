#include <iostream>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "Word.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    Word map;
    cout << "Вызов конструктора по умолчанию. Слово: ";
    map.Print();

    Word map1("Banans");
    cout << "Вызов конструктора инициализации слова заданным словом-инициализатором. Слово: ";
    map1.Print();

    Word map2("Q", 3);
    cout << "Вызов конструктора инициализации слова заданным количеством повторов заданного символа. Слово: ";
    map2.Print();

    Word map3("Zack", 4, true);
    cout << "Вызов конструктора инициализации слова частью заданного слова-инициализатора (первые n символов). Слово: ";
    map3.Print();

    Word map4(map3);
    cout << "Вызов конструктора копирования. Слово: ";
    map4.Print();

    Word map5(std::move(map3));
    cout << "Вызов конструктора перемещения. Слово: ";
    map5.Print();

    cout << "Введите слово для заполнения: ";
    map.zapoln();
    Word sortedWord = map.SortedWord();
    cout << "Отсортированное слово: ";
    sortedWord.Print();

    return 0;
}
