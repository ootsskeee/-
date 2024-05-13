#include <iostream>
#include <vector>
using namespace std;



void findSAMEcolumsandrows(const vector<vector<int>>& matrix) { // поиск совпадений строк и столбцов
    int n = matrix.size(); // определяем количество строк матрицы
    bool match = true; // переменная для отслеживания совпадений

    if (n == 0) {                  
        cout << "Матрица пуста." << endl;       // проверяем, что матрица не пуста и является квадратной
        return;
    }
    if (n != matrix[0].size()) {
        cout << "Матрица не квадратная." << endl;
        return;
    }

    // перебираем каждую строку и сравниваем ее с соответствующим столбцом
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != matrix[j][i]) { // если элементы не совпадают
                match = false; // устанавливаем флаг совпадения в false
                break;
            }
        }
        if (!match) {
            break; // если найдено несовпадение, прекращаем проверку
        }
    }

    // выводим результат на экран
    if (match) {
        cout << "Все строки совпадают с соответствующими столбцами." << endl;
    }
    else {
        cout << "Строки не совпадают со столбцами." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int n;
    cout << "Введите размер матрицы: ";   // получаем размер матрицы от пользователя
    cin >> n;

    // создаем матрицу и заполняем ее элементами
    vector<vector<int>> matrix(n, vector<int>(n)); // размер матрицы
    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Строка " << i + 1 << ":" << endl;
        for (int j = 0; j < n; ++j) { // заполнение матрицы элементами, введенными с клавиатуры
            cin >> matrix[i][j];
        }
    }

    // вызываем функцию для поиска совпадений строк и столбцов
    findSAMEcolumsandrows(matrix);
    return 0;
}
