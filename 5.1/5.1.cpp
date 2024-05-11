/*  Условие задания из первого семестра: 
Преобразовать строку: после каждой буквы 'z' добавить символ '!'. 
Получить в алфавитном порядке все согласные латинские буквы, входящие в строку
*/

#include <iostream>
#include <string>
#include <locale> 
#include <cctype> 
#include <algorithm> // для функции сортировки
using namespace std;


string transformString(const string& input_string) {  // преобразование строки
    string result;
    for (char c : input_string) {
        result += c;
        if (c == 'z') {
            result += '!';
        }
    }
    return result;
}

string findsoglasnieletters(const string& input_string) {  // поиск согласных букв
    string soglasnie;
    for (char c : input_string) {
        if (isalpha(c) && tolower(c) != 'a' && tolower(c) != 'e' && tolower(c) != 'i' && tolower(c) != 'o' && tolower(c) != 'u') {
            soglasnie += tolower(c);
        }
    }
    sort(soglasnie.begin(), soglasnie.end()); // сортировка согласных букв в алфавитном порядке
    return soglasnie;
}

int main() {
    setlocale(LC_ALL, "ru");
    string stroka;
    cout << "Введите строку: ";
    cin >> stroka;

    string stroka2 = transformString(stroka); // преобразование строки
    string soglasnie = findsoglasnieletters(stroka2); // поиск согласных букв

    cout << "Преобразованная строка: " << stroka2 << endl;
    cout << "Согласные буквы в алфавитном порядке: " << soglasnie << endl;
    return 0;
}

