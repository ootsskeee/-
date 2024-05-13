#pragma once
#include <algorithm>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

class Word {
private:
    char* word; // указатель на массив символов

public:
    Word();

    Word(const char* slovo);

    Word(const char* slovo, int num);

    // конструктор инициализации слова частью заданного слова-инициализатора (первые n символов или последние n символов)
    Word(const char* slovo, int num, bool firstPart);

    // конструктор копирования
    Word(const Word& slovo); 

    // конструктор перемещения
    Word(Word&& other) noexcept;

    // деструктор
    ~Word();

    // заполнение массива символов с клавиатуры
    void zapoln();

    // вывод информации об объекте
    void Print() const;

    // сортировка слова по возрастанию букв
    void Sort();

    // Метод для получения нового слова, буквы которого отсортированы в лексикографическом порядке
    Word SortedWord() const;
};