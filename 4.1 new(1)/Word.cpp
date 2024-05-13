#include "Word.h"

Word:: Word() {               // Конструктор по умолчанию
    word = new char[1];
    word[0] = '\0';
}

Word:: Word(const char* slovo) {                // конструктор инициализации слова заданным словом-инициализатором
    word = new char[strlen(slovo) + 1];
    strcpy_s(word, strlen(slovo) + 1, slovo);
}

Word:: Word(const char* slovo, int num) { // инициализация слова заданным количеством повторов заданного символа
    int len = strlen(slovo);
    word = new char[len * num + 1];
    int j = 0;
    for (int i = 0; i < num; i++) {
        for (int k = 0; k < len; k++) {
            word[j++] = slovo[k];
        }
    }
    word[j] = '\0';
}

// конструктор инициализации слова частью заданного слова-инициализатора (первые n символов или последние n символов)
Word:: Word(const char* slovo, int num, bool firstPart) {
    int len = strlen(slovo);
    word = new char[len * num + 1];
    int j = 0;
    if (firstPart) {
        for (int i = 0; i < num; i++) {
            for (int k = 0; k < len; k++) {
                word[j++] = slovo[k];
            }
        }
    }
    else {
        for (int i = 0; i < num; i++) {
            for (int k = len - 1; k >= 0; k--) {
                word[j++] = slovo[k];
            }
        }
    }
    word[j] = '\0';
}


// конструктор копирования
Word:: Word(const Word& slovo) {
    word = new char[strlen(slovo.word) + 1];
    strcpy_s(word, strlen(slovo.word) + 1, slovo.word);
}

// конструктор перемещения
Word:: Word(Word&& other) noexcept {
    word = other.word;
    other.word = nullptr;
}

// деструктор
Word:: ~Word() {
    delete[] word;
}

// заполнение массива символов с клавиатуры
void Word::zapoln() {
    char qwert[100];
    cin >> qwert;
    delete[] word;
    word = new char[strlen(qwert) + 1];
    strcpy_s(word, strlen(qwert) + 1, qwert);
}

// вывод информации об объекте
void Word::Print() const {
    cout << word << endl;
}

// сортировка слова по возрастанию букв
void Word::Sort() {
    sort(word, word + strlen(word));
}

// Метод для получения нового слова, буквы которого отсортированы в лексикографическом порядке
Word Word::SortedWord() const {
    Word sortedWord(*this); // копия текущего объекта
    sortedWord.Sort(); // сортировка буквы в копии
    return sortedWord; // возврат отсортированное слово
}