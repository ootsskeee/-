#include "Header.h"

using namespace std;

Vector::Vector() : size(1), Array(new int[1]) {
    Array[0] = 0;
}

Vector::Vector(int _size) : size(_size), Array(new int[_size]) {
    for (int i = 0; i < size; i++) {
        Array[i] = 0;
    }
}

Vector::Vector(const Vector& other) : size(other.size), Array(new int[other.size]) {
    for (int i = 0; i < size; i++) {
        Array[i] = other.Array[i];
    }
}

Vector::Vector(Vector&& other) noexcept : size(other.size), Array(other.Array) {
    other.size = 0;
    other.Array = nullptr;
}

Vector::~Vector() {
    delete[] Array;
}

void Vector::setSize(int _size) {
    size = _size;
    delete[] Array;
    Array = new int[size];
}

int Vector::getSize() const {
    return size;
}

int Vector::getElement(int index) const {
    if (index >= 0 && index < size) {
        return Array[index];
    }
    else {
        cout << "Выход за пределы" << endl;
        return 0;
    }
}

void Vector::setElement(int index, int value) {
    if (index >= 0 && index < size) {
        Array[index] = value;
    }
    else {
        cout << "Выход за пределы" << endl;
    }
}

void Vector::fillRandom() {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        Array[i] = rand() % 100; // генерация случайных чисел от 0 до 99
    }
}

void Vector::inputFromKeyboard() {
    std::cout << "Введите элементы вектора:\n";
    for (int i = 0; i < size; ++i) {
        cout << "Элемент " << i + 1 << ": ";
        cin >> Array[i];
    }
}

void Vector::print() const {
    for (int i = 0; i < size; i++) {
        cout << Array[i] << "\t";
    }
    cout << endl;
}

Vector Vector::operator+(const Vector& other) const {
    if (size != other.size) {
        throw invalid_argument("Ошибка размера");
    }
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.Array[i] = Array[i] + other.Array[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (size != other.size) {
        throw invalid_argument("Ошибка размера");
    }
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.Array[i] = Array[i] - other.Array[i];
    }
    return result;
}

Vector Vector::operator*(const Vector& other) const {
    if (size != other.size) {
        throw invalid_argument("Ошибка размера");
    }
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.Array[i] = Array[i] * other.Array[i];
    }
    return result;
}

Vector Vector::operator/(const Vector& other) const {
    if (size != other.size) {
        throw invalid_argument("Ошибка размера");
    }
    Vector result(size);
    for (int i = 0; i < size; i++) {
        if (other.Array[i] != 0) {
            result.Array[i] = Array[i] / other.Array[i];
        }
        else {
            throw invalid_argument("Деление на ноль");
        }
    }
    return result;
}

Vector Vector::operator*(float num) const {
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.Array[i] = Array[i] * num;
    }
    return result;
}

Vector Vector::operator/(float num) const {
    if (num == 0) {
        throw invalid_argument("Деление на ноль");
    }
    Vector result(size);
    for (int i = 0; i < size; i++) {
        result.Array[i] = Array[i] / num;
    }
    return result;
}

float Vector::length() const {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += Array[i] * Array[i];
    }
    return sqrt(sum);
}

Vector& Vector::operator=(const Vector& other) {
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

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        size = other.size;
        delete[] Array;
        Array = other.Array;
        other.size = 0;
        other.Array = nullptr;
    }
    return *this;
}
