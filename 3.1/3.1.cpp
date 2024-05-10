#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void separateNumbers(ifstream& fin, ofstream& gout, ofstream& positiveOut, ofstream& negativeOut) {
    // разделение на + и - числа, запись в соответствующий файл 
    int number; // для хранения числа
    bool isFirstNumber = true; // первое ли это число? 
    bool isPositive; // текущее число под знаком +?
    bool previousPositive = false; // знак предыдущего числа?

    while (fin >> number) { // считывает числа из файла, пока они есть
        isPositive = number >= 0;  // является ли текущее число положительным?

        if (!isFirstNumber && (isPositive == previousPositive)) {
            // eсли число не прошло проверку, то запись в соответствующий файл
            if (isPositive) {
                positiveOut << number << "\n";
            }
            else {
                negativeOut << number << "\n";
            }
            continue;
        }

        // если число прошло проверку, записываем его в gFile.txt
        gout << number << "\n";
        previousPositive = isPositive; // обновление значения флага предыдущего числа
        isFirstNumber = false; // сниятие флага с первого числа
    }
}

void writeRemainingNumbers(const char* positivePath, const char* negativePath, ofstream& gFile) {
    // запись оставшихся чисел, которые не прошли предыдущую проверку на + и -
    ifstream positiveFile(positivePath);
    ifstream negativeFile(negativePath);
    int posNumber, negNumber; // хранение этих чисел соответственно из положительного и отрицательного файлов

    // чтение первого числа из каждого файла
    positiveFile >> posNumber;
    negativeFile >> negNumber;

    // определение, с какого файла начать дополнительную запись
    bool writePositiveFirst = (posNumber < 0);

    while (positiveFile || negativeFile) {
        // запись числа из положительного файла
        if (positiveFile && writePositiveFirst) {
            gFile << posNumber << "\n";
            positiveFile >> posNumber;
        }
        // запись числа из отрицательного файла
        if (negativeFile && !writePositiveFirst) {
            gFile << negNumber << "\n";
            negativeFile >> negNumber;
        }

        // переключение между файлами
        writePositiveFirst = !writePositiveFirst;
    }

    positiveFile.close();
    negativeFile.close();
}

int main() {
    setlocale(LC_ALL, "Ru");
    const char fPath[] = "fFile.txt";
    const char gPath[] = "gFile.txt";
    const char positivePath[] = "positiveFile.txt";
    const char negativePath[] = "negativeFile.txt";

    ofstream fout(fPath);
    int amnt;

    if (fout.is_open()) {
        cout << "Введите количество чисел в файле: ";
        cin >> amnt;

        srand(time(0));

        for (int i = 1; i <= amnt; i++) {
            int randomNumber = rand() % 201 - 100;
            fout << randomNumber << "\n";
        }
        fout.close();
    }
    else {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    ifstream fin(fPath);
    ofstream gout(gPath);
    ofstream positiveOut(positivePath);
    ofstream negativeOut(negativePath);

    if (!fin.is_open() || !gout.is_open() || !positiveOut.is_open() || !negativeOut.is_open()) {
        cout << "Ошибка открытия файлов!" << endl;
        return 1;
    }

    separateNumbers(fin, gout, positiveOut, negativeOut);
    fin.close();
    gout.close();
    positiveOut.close();
    negativeOut.close();

    // открытие файла gFile.txt для дополнительной записи
    ofstream gFile(gPath, ios::app);
    if (!gFile.is_open()) {
        cout << "Ошибка открытия файла gFile.txt!" << endl;
        return 1;
    }

    // запись оставшихся чисел из positiveFile.txt и negativeFile.txt в gFile.txt
    writeRemainingNumbers(positivePath, negativePath, gFile);

    gFile.close();
    cout << "Готово!" << endl;
    system("notepad.exe fFile.txt");
    system("notepad.exe gFile.txt");
    return 0;
}
