// main.cpp
#include <iostream>
#include "Header.h"

using namespace std;

int main() {
    int N;
    cout << "������� ������ ��������: ";
    cin >> N;

    Vector vec;
    int size;

    cout << "������� ������ �������: ";
    cin >> size;
    vec.setSize(size);

    vec.inputFromKeyboard();

    Vector X(N);
    Vector Y(N);

    cout << "���������� ������� X: " << endl;
    X.fillRandom();
    X.print();

    cout << "���������� ������� Y: " << endl;
    Y.fillRandom();
    Y.print();

    int L;
    cout << "������� L: ";
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

    cout << "������ Z: " << endl;
    Z.print();

    return 0;
}
