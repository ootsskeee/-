#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Print(vector<int>& vectooor) {  // вывода элементов вектора
    for (int i = 0; i < vectooor.size(); i++) {
        cout << vectooor.at(i) << "\t";
    }
    cout << "\n" << "количество его элементов: " << vectooor.size() << "\n";
}

int CountOccurrences(const vector <int>& vecctor, int value) {
                                                   // определение, сколько раз определенное число встречается в векторе
    return count(vecctor.begin(), vecctor.end(), value);
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    cout << "Количество элементов в первом векторе: ";
    int fullElements = 0;
    cin >> fullElements;

    vector <int> firstVector;
    cout << "\n Как Вы хотите заполнять первый вектор?\n1. Рандомно\n2. С клавиатуры\n";

    char sh;
    cin >> sh;
    switch (sh) {
    case '1': {
        for (int i = 0; i < fullElements; i++) {
            int q = rand() % 20 - rand() % 20;
            firstVector.push_back(q);
        }
        break;
    }
    case '2': {
        cout << "Введите элементы вектора\n";
        for (int i = 0; i < fullElements; i++) {
            int q;
            cin >> q;
            firstVector.push_back(q);
        }
        break;
    }
    }

    cout << "\n Первый вектор:\n";
    Print(firstVector);
    sort(firstVector.begin(), firstVector.end());  // сортировка для простоты считывания и передачи элементов в 3-ий вектор 

    cout << "\n Первый вектор после сортировки:\n";
    Print(firstVector);

    cout << "Количество элементов во втором векторе: ";
    int second = 0;
    cin >> second;

    vector <int> secondVector;
    cout << "\n Как Вы хотите заполнять второй вектор?\n1. Рандомно\n2. С клавиатуры\n";

    char ch;
    cin >> ch;
    switch (ch) {
    case '1': {
        for (int i = 0; i < second; i++) {
            int q = rand() % 20 - rand() % 20;
            secondVector.push_back(q);
        }
        break;
    }
    case '2': {
        cout << "Введите элементы вектора\n";
        for (int i = 0; i < second; i++) {
            int q;
            cin >> q;
            secondVector.push_back(q);
        }
        break;
    }
    }

    cout << "\n Второй вектор:\n";
    Print(secondVector);
    sort(secondVector.begin(), secondVector.end());

    cout << "\n Второй вектор после сортировки:\n";
    Print(secondVector);
    cout << endl;

    vector <int> finalVector;

    cout << "\n Конечный вектор:\n";
    for (int i = 0; i < firstVector.size(); i++) {
        if (CountOccurrences(firstVector, firstVector[i]) == 2 && count(finalVector.begin(), finalVector.end(), firstVector[i]) == 0) {
            finalVector.push_back(firstVector[i]);
        }
    }

    for (int i = 0; i < secondVector.size(); i++) {
        if (CountOccurrences(secondVector, secondVector[i]) == 2 && count(finalVector.begin(), finalVector.end(), secondVector[i]) == 0) {
            finalVector.push_back(secondVector[i]);
        }
    }

    Print(finalVector);
    return 0;
}
