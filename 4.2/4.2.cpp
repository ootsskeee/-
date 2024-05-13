#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>
using namespace std;


class Student {
private:
    char name[50];
    unsigned age;
    unsigned course;
    bool pol; // 1 - мужской, 0 - женский
    unsigned core; // оценка успеваемости

public:
    // Конструкторы
    Student() : age(18), course(1), pol(true), core(3) {
        strcpy_s(name, "Ваня");
    }

    Student(const char* _name, unsigned _age, unsigned _course, bool _pol, unsigned _core)
        : age(_age), course(_course), pol(_pol), core(_core) {
        strcpy_s(name, _name);
    }

    Student(const Student& other) {
        strcpy_s(name, other.name);
        age = other.age;
        course = other.course;
        pol = other.pol;
        core = other.core;
    }

    Student(Student&& other) noexcept {
        strcpy_s(name, other.name);
        age = other.age;
        course = other.course;
        pol = other.pol;
        core = other.core;
        strcpy_s(other.name, "");
        other.age = 0;
        other.course = 0;
        other.pol = false;
        other.core = 0;
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            strcpy_s(name, other.name);
            age = other.age;
            course = other.course;
            pol = other.pol;
            core = other.core;
        }
        return *this;
    }

    // Деструктор
    ~Student() = default;

    // Методы
    void ReadFromKeyboard() {
        cout << "\nВведите имя студента: ";
        cin.getline(name, sizeof(name)); // Считываем строку имени

        cout << "\nВведите возраст студента: ";
        cin >> age;
        cin.ignore(1, '\n'); // Очищаем символ новой строки

        cout << "\nВведите курс: ";
        cin >> course;
        cin.ignore(1, '\n'); // Очищаем символ новой строки

        cout << "\nВведите пол студента (1-муж, 0-жен): ";
        cin >> pol;
        cin.ignore(1, '\n'); // Очищаем символ новой строки

        cout << "\nВведите средний балл: ";
        cin >> core;
    }



    void ReadFromFile(ifstream& infile) {
        infile.read(reinterpret_cast<char*>(&age), sizeof(age));
        infile.read(reinterpret_cast<char*>(&course), sizeof(course));
        infile.read(reinterpret_cast<char*>(&pol), sizeof(pol));
        infile.read(reinterpret_cast<char*>(&core), sizeof(core));
        infile.read(name, sizeof(name));
    }

    void WriteToFile(ofstream& outfile) const {
        outfile.write(reinterpret_cast<const char*>(&age), sizeof(age));
        outfile.write(reinterpret_cast<const char*>(&course), sizeof(course));
        outfile.write(reinterpret_cast<const char*>(&pol), sizeof(pol));
        outfile.write(reinterpret_cast<const char*>(&core), sizeof(core));
        outfile.write(name, sizeof(name));
    }

    void Print() const {
        cout << "Имя: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Курс: " << course << endl;
        cout << "Пол: " << (pol ? "мужской" : "женский") << endl;
        cout << "Средний балл: " << core << endl;
        cout << endl;
    }

    // Геттеры и сеттеры
    char* GetName() { return name; }
    void SetName(const char* _name) { strcpy_s(name, _name); }

    unsigned GetAge() const { return age; }
    void SetAge(unsigned _age) { age = _age; }

    unsigned GetCourse() const { return course; }
    void SetCourse(unsigned _course) { course = _course; }

    bool GetPol() const { return pol; }
    void SetPol(bool _pol) { pol = _pol; }

    unsigned GetCore() const { return core; }
    void SetCore(unsigned _core) { core = _core; }
};

int main() {
    setlocale(LC_ALL, "rus");

    int count;
    cout << "Введите количество студентов: ";
    cin >> count;

    // Сбрасываем буфер ввода
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Student* students = new Student[count];

    for (int i = 0; i < count; ++i) {
        cout << "\nСтудент " << i + 1 << ":" << endl;
        students[i].ReadFromKeyboard();
    }

    for (int i = 0; i < count; ++i) {
        cout << "\nДанные студента " << i + 1 << ":" << endl;
        students[i].Print();
    }

    unsigned course;
    cout << "Введите номер курса для расчета среднего балла успеваемости: ";
    cin >> course;

    unsigned totalCore = 0;
    unsigned numStudentsOnCourse = 0;
    for (int i = 0; i < count; ++i) {
        if (students[i].GetCourse() == course) {
            totalCore += students[i].GetCore();
            ++numStudentsOnCourse;
        }
    }

    if (numStudentsOnCourse > 0) {
        float averageCore = static_cast<float>(totalCore) / numStudentsOnCourse;
        cout << "Средний балл успеваемости студентов " << course << " курса: " << fixed << setprecision(2) << averageCore << endl;
    }
    else {
        cout << "На " << course << " курсе нет студентов." << endl;
    }

    delete[] students;
    return 0;
}
