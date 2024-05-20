// main.cpp
#include <iostream>
#include "Header.h"

using namespace std;

int main() {
    int N;
    cout << "Введите размер векторов: ";
    cin >> N;

    Vector vec;
    int size;

    cout << "Введите размер вектора: ";
    cin >> size;
    vec.setSize(size);

    vec.inputFromKeyboard();

    Vector X(N);
    Vector Y(N);

    cout << "Заполнение вектора X: " << endl;
    X.fillRandom();
    X.print();

    cout << "Заполнение вектора Y: " << endl;
    Y.fillRandom();
    Y.print();

    int L;
    cout << "Введите L: ";
    cin >> L;

    Vector Z(N);
    for (int i = 0; i < N; i++) {
        if (i >= L && i < N - L) {
            int xi = X.getElement(i);
            int yi = Y.getElement(i);
            int xil = X.getElement(i - L);
            int yil = Y.getElement(i - L);
            Z.setElement(i, xi * yi + xil * yil);
        }
    }

    cout << "Вектор Z: " << endl;
    Z.print();

    return 0;
}
