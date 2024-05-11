/*
Числа в двоичной и шестнадцатеричной системах счисления представлять как
строки с проверкой правильного ввода числа.
Числа в десятичной системе – как целые числа.
При переводе реализовать алгоритмы перевода чисел из одной системы счисления в другую самостоятельно.
5. Написать программу перевода целых чисел из десятичной системы счисления в шестнадцатеричную.
*/

#include <iostream>
#include <string>
#include <algorithm> // для функции reverse
using namespace std;


string translatenumber(int numb) {
    const string hexadecimal = "0123456789ABCDEF";
    string result;

    while (numb > 0) {  // перевод из десятичной в шестнадцатеричную систему счисления
        int remainder = numb % 16;
        result += hexadecimal[remainder];
        numb /= 16;
    }

    reverse(result.begin(), result.end()); // т.к. результат возвращается в обратном порядке, поэтому переворачиваем его
    return result;
}



int main() {
    setlocale(LC_ALL, "russian");
    string str;
    cout << "Введите число в десятичной системе: " << endl;
    cin >> str;

    // проверка правильности ввода числа
    if (str.find_first_not_of("0123456789-") != string::npos || (str.find('-') != string::npos && str.find('-') != 0)) {
        cout << "Неверный ввод числа." << endl;
        return 0;
    }

    int numb = stoi(str); // преобразует в тип int

    // если число отрицательное, меняем знак и продолжаем работу с абсолютным значением
    bool isNegative = false;
    if (numb < 0) {
        isNegative = true;
        numb *= -1;
    }

    string result = translatenumber(numb);

    // если число было отрицательным, добавляем знак минус
    if (isNegative)
        result = "-" + result;

    cout << "В 16-ой системе: " << result << endl;
    return 0;
}