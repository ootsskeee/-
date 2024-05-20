#pragma once
// Vector.h
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>
#include <ctime>

class Vector {
private:
    int size;
    int* Array;
    static const int MaxNum = 1000;

public:
    Vector();
    Vector(int _size);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    void setSize(int _size);
    int getSize() const;

    int getElement(int index) const;
    void setElement(int index, int value);

    void fillRandom();
    void inputFromKeyboard();
    void print() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(const Vector& other) const;
    Vector operator/(const Vector& other) const;
    Vector operator*(float num) const;
    Vector operator/(float num) const;

    float length() const;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
};

#endif // VECTOR_H
