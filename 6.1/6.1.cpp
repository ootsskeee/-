#include <iostream>
#include <string>
#include <vector>
using namespace std;


// "вклад до востребования"
class Deposit {
protected:
    string accountNumber;  // номер счета
    string creationDate;   // дата открытия вклада
    double annualInterestRate;  // годовая процентная ставка
    double currentAmount;  // текущая сумма на вкладе


public:
    // конструктор с параметрами и проверкой на положительные значения
    Deposit(const string& accNum, const string& date, double rate, double amount)
        : accountNumber(accNum), creationDate(date), annualInterestRate(rate), currentAmount(amount) {
        if (rate < 0 || amount < 0) {
            cerr << "Ошибка: Процентная ставка и текущая сумма должны быть положительными." << endl;
            annualInterestRate = 0;
            currentAmount = 0;
        }
    }


    // отображение информации о вкладе
    virtual void display() const {
        cout << "Номер счёта: " << accountNumber << "\n"
            << "Дата открытия: " << creationDate << "\n"
            << "Годовая процентная ставка: " << annualInterestRate << "%\n"
            << "Текущая сумма: " << currentAmount << "\n";
    }

    virtual ~Deposit() = default;  // деструктор


    // получение значений полей
    string getAccountNumber() const { return accountNumber; }
    string getCreationDate() const { return creationDate; }
    double getAnnualInterestRate() const { return annualInterestRate; }
    double getCurrentAmount() const { return currentAmount; }


    // установка значений полей с проверкой допустимости
    void setAnnualInterestRate(double rate) {
        if (rate < 0) {
            cerr << "Ошибка: Процентная ставка должна быть положительной." << endl;
            return;
        }
        annualInterestRate = rate;
    }

    void setCurrentAmount(double amount) {
        if (amount < 0) {
            cerr << "Ошибка: Текущая сумма должна быть положительной." << endl;
            return;
        }
        currentAmount = amount;
    }
};

// "вклад до востребования"
class OnDemandDeposit : public Deposit {
public:
    // конструктор с параметрами
    OnDemandDeposit(const string& accNum, const string& date, double rate, double amount)
        : Deposit(accNum, date, rate, amount) {}


    // отображение информации о вкладе
    void display() const override {
        cout << "Вклад до востребования:\n";
        Deposit::display();
    }
};

// "условный вклад"
class ConditionalDeposit : public Deposit {
private:
    string closureCondition;  // есловие закрытия вклада

public:
    // конструктор с параметрами и проверкой на пустое условие закрытия
    ConditionalDeposit(const string& accNum, const string& date, double rate, double amount, const string& condition)
        : Deposit(accNum, date, rate, amount), closureCondition(condition) {
        if (condition.empty()) {
            cerr << "Ошибка: Условие закрытия не может быть пустым." << endl;
            closureCondition = "Не указано";
        }
    }

    // отображение информации о вкладе
    void display() const override {
        cout << "Условный вклад:\n";
        Deposit::display();
        cout << "Условие закрытия: " << closureCondition << "\n";
    }

    // получение значения поля
    string getClosureCondition() const { return closureCondition; }


    // установка значения поля с проверкой допустимости
    void setClosureCondition(const string& condition) {
        if (condition.empty()) {
            cerr << "Ошибка: Условие закрытия не может быть пустым." << endl;
            return;
        }
        closureCondition = condition;
    }
};

//  "срочный безотзывной вклад"
class FixedNonRevocableDeposit : public Deposit {
private:
    int depositTerm;  // срок вклада в месяцах
    int additionalContributionPeriod;  // период для дополнительных взносов

public:
    // проверка на положительные значения
    FixedNonRevocableDeposit(const string& accNum, const string& date, double rate, double amount, int term, int contributionPeriod)
        : Deposit(accNum, date, rate, amount), depositTerm(term), additionalContributionPeriod(contributionPeriod) {
        if (term <= 0 || contributionPeriod < 0) {
            cerr << "Ошибка: Срок вклада и период дополнительных взносов должны быть положительными." << endl;
            depositTerm = 0;
            additionalContributionPeriod = 0;
        }
    }

    // отображение информации о вкладе
    void display() const override {
        cout << "Срочный безотзывной вклад:\n";
        Deposit::display();
        cout << "Срок вклада: " << depositTerm << " месяцев\n"
            << "Период для дополнительных взносов: " << additionalContributionPeriod << " месяцев\n";
    }


    // получение значений полей
    int getDepositTerm() const { return depositTerm; }
    int getAdditionalContributionPeriod() const { return additionalContributionPeriod; }


    // установка значений полей с проверкой допустимости
    void setDepositTerm(int term) {
        if (term <= 0) {
            cerr << "Ошибка: Срок вклада должен быть положительным." << endl;
            return;
        }
        depositTerm = term;
    }

    void setAdditionalContributionPeriod(int period) {
        if (period < 0) {
            cerr << "Ошибка: Период дополнительных взносов должен быть положительным." << endl;
            return;
        }
        additionalContributionPeriod = period;
    }
};

// "срочный отзывной вклад"
class FixedRevocableDeposit : public Deposit {
private:
    int depositTerm;  // срок вклада в месяцах
    double reducedInterestRate;  // пониженная процентная ставка в случае досрочного расторжения
    double initialAmount;  // начальная сумма для пересчёта процентов по пониженной ставке

public:
    // укструктор с параметрами и проверкой на положительные значения
    FixedRevocableDeposit(const string& accNum, const string& date, double rate, double amount, int term, double reducedRate, double initialAmt)
        : Deposit(accNum, date, rate, amount), depositTerm(term), reducedInterestRate(reducedRate), initialAmount(initialAmt) {
        if (term <= 0 || reducedRate < 0 || initialAmt < 0) {
            cerr << "Ошибка: Срок вклада, пониженная процентная ставка и начальная сумма должны быть положительными." << endl;
            depositTerm = 0;
            reducedInterestRate = 0;
            initialAmount = 0;
        }
    }

    // отображение информации о вкладе
    void display() const override {
        cout << "Срочный отзывной вклад:\n";
        Deposit::display();
        cout << "Срок вклада: " << depositTerm << " месяцев\n"
            << "Пониженная процентная ставка: " << reducedInterestRate << "%\n"
            << "Начальная сумма: " << initialAmount << "\n";
    }


    // получение значений полей
    int getDepositTerm() const { return depositTerm; }
    double getReducedInterestRate() const { return reducedInterestRate; }
    double getInitialAmount() const { return initialAmount; }


    // установка значений полей с проверкой допустимости
    void setDepositTerm(int term) {
        if (term <= 0) {
            cerr << "Ошибка: Срок вклада должен быть положительным." << endl;
            return;
        }
        depositTerm = term;
    }

    void setReducedInterestRate(double rate) {
        if (rate < 0) {
            cerr << "Ошибка: Пониженная процентная ставка должна быть положительной." << endl;
            return;
        }
        reducedInterestRate = rate;
    }

    void setInitialAmount(double amount) {
        if (amount < 0) {
            cerr << "Ошибка: Начальная сумма должна быть положительной." << endl;
            return;
        }
        initialAmount = amount;
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    vector <Deposit*> deposits;  // вектор указателей на вклады

    // создание различных вкладов и добавление их в вектор
    deposits.push_back(new OnDemandDeposit("12345", "2023-01-01", 1.5, 10000.0));
    deposits.push_back(new ConditionalDeposit("23456", "2023-02-01", 2.0, 15000.0, "До свадьбы"));
    deposits.push_back(new FixedNonRevocableDeposit("34567", "2023-03-01", 2.5, 20000.0, 12, 6));
    deposits.push_back(new FixedRevocableDeposit("45678", "2023-04-01", 3.0, 25000.0, 24, 1.5, 20000.0));

    // отображение информации о каждом вкладе
    for (const auto& deposit : deposits) {
        deposit->display();
        cout << "\n";
    }

    // освобождение памяти
    for (auto& deposit : deposits) {
        delete deposit;
    }

    return 0;
}