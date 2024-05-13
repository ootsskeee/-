#include<iostream>
#include<cmath>
#include<ctime>

using namespace std;

class Vector {
private:
    int size;
    int* Array;
    const int MaxNum = 1000;

public:
    Vector() : size(1), Array(new int[1]) {
        Array[0] = 0;
    }

    Vector(int _size) : size(_size), Array(new int[_size]) {
        for (int i = 0; i < size; i++) {
            Array[i] = 0;
        }
    }

    Vector(const Vector& other) : size(other.size), Array(new int[other.size]) {
        for (int i = 0; i < size; i++) {
            Array[i] = other.Array[i];
        }
    }

    Vector(Vector&& other) noexcept : size(other.size), Array(other.Array) {
        other.size = 0;
        other.Array = nullptr;
    }

    ~Vector() {
        delete[] Array;
    }

    void setSize(int _size) {
        size = _size;
        delete[] Array;
        Array = new int[size];
    }

    int getSize() const {
        return size;
    }

    void setElement(int index, int value) {
        if (index >= 0 && index < size) {
            Array[index] = value;
        }
        else {
            cout << "Выход за пределы" << endl;
        }
    }

    int getElement(int index) const {
        if (index >= 0 && index < size) {
            return Array[index];
        }
        else {
            cout << "Выход за пределы" << endl;
            return 0;
        }
    }

    void fillRandom() {
        srand(time(0));
        for (int i = 0; i < size; i++) {
            Array[i] = rand() % 100; // генерация случайных чисел от 0 до 99
        }
    }

    void inputFromKeyboard() {
        std::cout << "Введите элементы вектора:\n";
        for (int i = 0; i < size; ++i) {
            cout << "Элемент " << i + 1 << ": ";
            cin >> Array[i];
        }
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            cout << Array[i] << "\t";
        }
        cout << endl;
    }

    Vector operator*(float num) const {
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.Array[i] = Array[i] * num;
        }
        return result;
    }

    friend Vector operator*(const Vector& lhs, const Vector& rhs);

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            size = other.size;
            delete[] Array;
            Array = new int[size];
            for (int i = 0; i < size; i++) {
                Array[i] = other.Array[i];
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            size = other.size;
            delete[] Array;
            Array = other.Array;
            other.size = 0;
            other.Array = nullptr;
        }
        return *this;
    }
};

Vector operator*(const Vector& lhs, const Vector& rhs) {
    if (lhs.getSize() != rhs.getSize()) {
        throw invalid_argument("Ошибка размера");
    }
    Vector result(lhs.getSize());
    for (int i = 0; i < lhs.getSize(); i++) {
        result.setElement(i, lhs.getElement(i) * rhs.getElement(i));
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "rus");
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
            Z.setElement(i, X.getElement(i) * Y.getElement(i) + X.getElement(i - L) * Y.getElement(i - L));
        }
    }

    cout << "Вектор Z: " << endl;
    Z.print();

    return 0;
}