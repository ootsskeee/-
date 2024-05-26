#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    int row, collmn;
    int choice;

    cout << "Введите кол-во строк: ";
    cin >> row;
    cout << "Введите кол-во столбцов: ";
    cin >> collmn;

    // матрица
    vector <vector <int>> Matrix(row, vector <int>(collmn));

    cout << "Выберите способ заполнения матрицы (1 - random, 2 - с клавиатуры): ";
    cin >> choice;

    switch (choice) {
    case 1:
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < collmn; ++j) {
                Matrix[i][j] = rand() % 10 - 5; // от -5 до 4
            }
        }
        break;
    case 2:
        cout << "Введите элементы матрицы:" << endl;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < collmn; ++j) {
                cout << "Матрица [" << i << "][" << j << "]: ";
                cin >> Matrix[i][j];
            }
        }
        break;
    default:
        cout << "Неверно!!!" << endl;
        return 1;
    }

    // вывод матрицы
    cout << "Матрица:" << endl;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < collmn; ++j) {
            cout << Matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    // поиск строк, которые совпадают с соответствующими столбцами
    vector <int> matchingIndices;
    for (int k = 0; k < min(row, collmn); ++k) {
        bool match = true;
        for (int i = 0; i < row; ++i) {
            if (Matrix[k][i] != Matrix[i][k]) {
                match = false;
                break;
            }
        }
        if (match) {
            matchingIndices.push_back(k + 1); // k + 1, потому что натуральные числа начинаются с 1
        }
    }

    // вывод
    if (matchingIndices.empty()) {
        cout << "Ни одна строка и ни один столбец не совпадают." << endl;
    }
    else {
        cout << "Сопоставимые индексы строк и столбцов: ";
        for (int index : matchingIndices) {
            cout << index << " ";
        }
        cout << endl;
    }

    return 0;
}