#pragma once
#include <algorithm>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

class Word {
private:
    char* word; // ��������� �� ������ ��������

public:
    Word();

    Word(const char* slovo);

    Word(const char* slovo, int num);

    // ����������� ������������� ����� ������ ��������� �����-�������������� (������ n �������� ��� ��������� n ��������)
    Word(const char* slovo, int num, bool firstPart);

    // ����������� �����������
    Word(const Word& slovo); 

    // ����������� �����������
    Word(Word&& other) noexcept;

    // ����������
    ~Word();

    // ���������� ������� �������� � ����������
    void zapoln();

    // ����� ���������� �� �������
    void Print() const;

    // ���������� ����� �� ����������� ����
    void Sort();

    // ����� ��� ��������� ������ �����, ����� �������� ������������� � ������������������ �������
    Word SortedWord() const;
};