#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Student {
private:
    string name;
    unsigned age;
    unsigned course;
    bool pol; // 1 - мужской, 0 - женский
    unsigned core; // для оценки успеваемости

public:
    // конструктор по умолчанию 
    Student() : name("Ivanov Ivan Ivanovich"),
        age(18),
        course(1),
        pol(true),
        core(3) {}

    // конструктор с параметрами
    Student(const string& _name, unsigned _age, unsigned _course, bool _pol, unsigned _core)
        : name(_name),
        age(_age),
        course(_course),
        pol(_pol),
        core(_core) {}

    // конструктор копирования
    Student(const Student& other)
        : name(other.name),
        age(other.age),
        course(other.course),
        pol(other.pol),
        core(other.core) {}


    // конструктор перемещения
    Student(Student&& other) noexcept
        : name(move(other.name)),
        age(other.age),
        course(other.course),
        pol(other.pol),
        core(other.core) {

        other.age = 0;
        other.course = 0;
        other.pol = false;
        other.core = 0;
    }

    // оператор копирующего присваивания
    Student& operator=(const Student& other) {
        if (this != &other) { // проверка на самоприсваивание
            name = other.name;
            age = other.age;
            course = other.course;
            pol = other.pol;
            core = other.core;
        }
        return *this;
    }


    // оператор перемещающего присваивания
    Student& operator=(Student&& other) noexcept {
        if (this != &other) {
            name = move(other.name);
            age = other.age;
            course = other.course;
            pol = other.pol;
            core = other.core;
            other.age = 0;
            other.course = 0;
            other.pol = false;
            other.core = 0;
        }
        return *this;
    }

    // Деструктор
    ~Student() = default;

    void ReadFromKeyboard() { // заполнение полей с клавиатуры
        cout << "\nВведите FIO студента: ";
        cin.ignore(); // сбрасываем буфер ввода
        getline(cin, name); // считываем строку имени

        cout << "Введите возраст студента: ";
        cin >> age;

        cout << "Введите курс: ";
        cin >> course;

        cout << "Введите пол студента (1-муж, 0-жен): ";
        cin >> pol;

        cout << "Введите средний балл: ";
        cin >> core;
    }

    void ReadFromFile(ifstream& infile) { // загрузка из бинарного файла
        size_t name_length;
        infile.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
        name.resize(name_length);
        infile.read(&name[0], name_length);
        infile.read(reinterpret_cast<char*>(&age), sizeof(age));
        infile.read(reinterpret_cast<char*>(&course), sizeof(course));
        infile.read(reinterpret_cast<char*>(&pol), sizeof(pol));
        infile.read(reinterpret_cast<char*>(&core), sizeof(core));
    }

    void WriteToFile(ofstream& outfile) const { //сохранение в бинарный файл
        size_t name_length = name.size();
        outfile.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
        outfile.write(name.c_str(), name_length);
        outfile.write(reinterpret_cast<const char*>(&age), sizeof(age));
        outfile.write(reinterpret_cast<const char*>(&course), sizeof(course));
        outfile.write(reinterpret_cast<const char*>(&pol), sizeof(pol));
        outfile.write(reinterpret_cast<const char*>(&core), sizeof(core));
    }

    void Print() const { // вывод 
        cout << "ФИО: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Курс: " << course << endl;
        cout << "Пол: " << (pol ? "мужской" : "женский") << endl;
        cout << "Средний балл: " << core << endl;
        cout << endl;
    }

    // методы получения и установки полей класса
    string GetName() const { return name; }
    void SetName(const string& _name) { name = _name; }

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

    Student* students = new Student[count]; // динам. массив из объектa Student 

    for (int i = 0; i < count; ++i) {
        cout << "\nСтудент " << i + 1 << ":" << endl;
        students[i].ReadFromKeyboard();  // vvod info about student
    }

    // сохранение студентов в файл
    ofstream outfile("students.bin", ios::binary);
    for (int i = 0; i < count; ++i) {
        students[i].WriteToFile(outfile);
    }
    outfile.close();

    // загрузка студентов из файла
    ifstream infile("students.bin", ios::binary);
    for (int i = 0; i < count; ++i) {
        students[i].ReadFromFile(infile);
    }
    infile.close();

    for (int i = 0; i < count; ++i) {
        cout << "\nДанные студента " << i + 1 << ":" << endl;
        students[i].Print();
    }

    unsigned course; // номер курса, введенный пользователем 
    cout << "Введите номер курса для расчета среднего балла успеваемости: ";
    cin >> course;

    unsigned totalCore = 0; // для хранения общей оценки на N курсе
    unsigned numStudentsOnCourse = 0; // счетчик студентов на курсе 
    for (int i = 0; i < count; ++i) {
        if (students[i].GetCourse() == course) { // на том ли курсе студетн? 
            totalCore += students[i].GetCore(); // если на нужном курсе, то его ср. балл учитывется 
            ++numStudentsOnCourse;
        }
    }

    // вывод ср. балла 
    if (numStudentsOnCourse > 0) { // есть ли студет 
        float averageCore = static_cast<float>(totalCore) / numStudentsOnCourse;
        cout << "Средний балл успеваемости студентов " << course << " курса: " << fixed << setprecision(2) << averageCore << endl;
    }
    else {
        cout << "На " << course << " курсе нет студентов." << endl;
    }

    delete[] students;
    return 0;
}