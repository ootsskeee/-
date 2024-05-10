#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void separateNumbers(ifstream& fin, ofstream& gout, ofstream& positiveOut, ofstream& negativeOut) {
    int number;
    bool isFirstNumber = true;
    bool isPositive;
    bool previousPositive = false;

    while (fin.read(reinterpret_cast<char*>(&number), sizeof(number))) {
        isPositive = number >= 0;

        if (!isFirstNumber && (isPositive == previousPositive)) {
            // если число не прошло проверку, записываем его в соответствующий файл
            if (isPositive) {
                positiveOut.write(reinterpret_cast<const char*>(&number), sizeof(number));
            }
            else {
                negativeOut.write(reinterpret_cast<const char*>(&number), sizeof(number));
            }
            continue;
        }

        // если число прошло проверку, записываем его в gFile.txt
        gout.write(reinterpret_cast<const char*>(&number), sizeof(number));
        previousPositive = isPositive;
        isFirstNumber = false;
    }
}

void writeRemainingNumbers(const char* positivePath, const char* negativePath, ofstream& gFile) {
    ifstream positiveFile(positivePath, ios::binary);
    ifstream negativeFile(negativePath, ios::binary);
    int posNumber, negNumber;

    // чтение первого числа из каждого файла
    positiveFile.read(reinterpret_cast<char*>(&posNumber), sizeof(posNumber));
    negativeFile.read(reinterpret_cast<char*>(&negNumber), sizeof(negNumber));

    // определение, с какого файла начать дополнительную запись
    bool writePositiveFirst = (posNumber < 0);

    while (positiveFile || negativeFile) {
        // запись числа из положительного файла, если необходимо
        if (positiveFile && writePositiveFirst) {
            gFile.write(reinterpret_cast<const char*>(&posNumber), sizeof(posNumber));
            positiveFile.read(reinterpret_cast<char*>(&posNumber), sizeof(posNumber));
        }
        // запись числа из отрицательного файла, если необходимо
        if (negativeFile && !writePositiveFirst) {
            gFile.write(reinterpret_cast<const char*>(&negNumber), sizeof(negNumber));
            negativeFile.read(reinterpret_cast<char*>(&negNumber), sizeof(negNumber));
        }

        // переключение между файлами
        writePositiveFirst = !writePositiveFirst;
    }

    positiveFile.close();
    negativeFile.close();
}

int main() {
    setlocale(LC_ALL, "Ru");
    const char fPath[] = "fFile.bin";
    const char gPath[] = "gFile.bin";
    const char positivePath[] = "positiveFile.bin";
    const char negativePath[] = "negativeFile.bin";

    ofstream fout(fPath, ios::binary);
    int amnt; 

    if (fout.is_open()) {
        cout << "Введите количество чисел в файле: ";
        cin >> amnt;

        srand(time(0));

        for (int i = 1; i <= amnt; i++) {
            int randomNumber = rand() % 201 - 100;
            fout.write(reinterpret_cast<const char*>(&randomNumber), sizeof(randomNumber));
        }
        fout.close();
    }
    else {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    ifstream fin(fPath, ios::binary);
    ofstream gout(gPath, ios::binary);
    ofstream positiveOut(positivePath, ios::binary);
    ofstream negativeOut(negativePath, ios::binary);

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
    ofstream gFile(gPath, ios::app | ios::binary);
    if (!gFile.is_open()) {
        cout << "Ошибка открытия файла gFile.txt!" << endl;
        return 1;
    }

    // запись оставшихся чисел из positiveFile.txt и negativeFile.txt в gFile.txt
    writeRemainingNumbers(positivePath, negativePath, gFile);

    gFile.close();
    cout << "Готово!" << endl;
    system("notepad.exe fFile.bin");
    system("notepad.exe gFile.bin");
    return 0;
}