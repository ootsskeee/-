#include "Word.h"

Word:: Word() {               // ����������� �� ���������
    word = new char[1];
    word[0] = '\0';
}

Word:: Word(const char* slovo) {                // ����������� ������������� ����� �������� ������-���������������
    word = new char[strlen(slovo) + 1];
    strcpy_s(word, strlen(slovo) + 1, slovo);
}

Word:: Word(const char* slovo, int num) { // ������������� ����� �������� ����������� �������� ��������� �������
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

// ����������� ������������� ����� ������ ��������� �����-�������������� (������ n �������� ��� ��������� n ��������)
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


// ����������� �����������
Word:: Word(const Word& slovo) {
    word = new char[strlen(slovo.word) + 1];
    strcpy_s(word, strlen(slovo.word) + 1, slovo.word);
}

// ����������� �����������
Word:: Word(Word&& other) noexcept {
    word = other.word;
    other.word = nullptr;
}

// ����������
Word:: ~Word() {
    delete[] word;
}

// ���������� ������� �������� � ����������
void Word::zapoln() {
    char qwert[100];
    cin >> qwert;
    delete[] word;
    word = new char[strlen(qwert) + 1];
    strcpy_s(word, strlen(qwert) + 1, qwert);
}

// ����� ���������� �� �������
void Word::Print() const {
    cout << word << endl;
}

// ���������� ����� �� ����������� ����
void Word::Sort() {
    sort(word, word + strlen(word));
}

// ����� ��� ��������� ������ �����, ����� �������� ������������� � ������������������ �������
Word Word::SortedWord() const {
    Word sortedWord(*this); // ����� �������� �������
    sortedWord.Sort(); // ���������� ����� � �����
    return sortedWord; // ������� ��������������� �����
}