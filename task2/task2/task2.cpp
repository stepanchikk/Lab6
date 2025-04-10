#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Pracivnyk {
public:
    virtual double narakhuvannyaZarplaty() const = 0;
    virtual void info() const = 0;
    virtual ~Pracivnyk() {
        cout << "Видалено базовий об'єкт Pracivnyk" << endl;
    }
};

class PohodynnyiSluzhbovets : public Pracivnyk {
private:
    double godynnaStavka;
    int kilkistGodyn;
public:
    PohodynnyiSluzhbovets(double stavka, int godyn) : godynnaStavka(stavka), kilkistGodyn(godyn) {
        cout << "Створено об'єкт: Погодинний службовець" << endl;
    }

    ~PohodynnyiSluzhbovets() override {
        cout << "Видалено об'єкт: Погодинний службовець" << endl;
    }

    double narakhuvannyaZarplaty() const override {
        return godynnaStavka * kilkistGodyn;
    }

    void info() const override {
        cout << "Погодинний службовець, ставка: " << godynnaStavka
            << ", годин: " << kilkistGodyn
            << ", зарплата: " << narakhuvannyaZarplaty() << " грн" << endl;
    }
};

class ShtatnyiSluzhbovets : public Pracivnyk {
private:
    double misiachnaZarplata;
public:
    ShtatnyiSluzhbovets(double zarplata) : misiachnaZarplata(zarplata) {
        cout << "Створено об'єкт: Штатний службовець" << endl;
    }

    ~ShtatnyiSluzhbovets() override {
        cout << "Видалено об'єкт: Штатний службовець" << endl;
    }

    double narakhuvannyaZarplaty() const override {
        return misiachnaZarplata;
    }

    void info() const override {
        cout << "Штатний службовець, зарплата: " << narakhuvannyaZarplaty() << " грн" << endl;
    }
};

class SluzhbovetsZProcentom : public Pracivnyk {
private:
    double obsiagProdazh;
    double procent;
public:
    SluzhbovetsZProcentom(double obsiag, double protsent) : obsiagProdazh(obsiag), procent(protsent) {
        cout << "Створено об'єкт: Службовець з процентною ставкою" << endl;
    }

    ~SluzhbovetsZProcentom() override {
        cout << "Видалено об'єкт: Службовець з процентною ставкою" << endl;
    }

    double narakhuvannyaZarplaty() const override {
        return obsiagProdazh * (procent / 100.0);
    }

    void info() const override {
        cout << "Службовець з процентною ставкою, обсяг продаж: " << obsiagProdazh
            << ", % ставка: " << procent
            << ", зарплата: " << narakhuvannyaZarplaty() << " грн" << endl;
    }
};

// Створення об'єктів (не змінилось)
PohodynnyiSluzhbovets* stvorytyPohodynnoho(bool random) {
    if (random) {
        double stavka = 100 + rand() % 101;
        int godyn = 120 + rand() % 81;
        return new PohodynnyiSluzhbovets(stavka, godyn);
    }
    else {
        double stavka;
        int godyn;
        cout << "Введіть погодинну ставку: ";
        cin >> stavka;
        cout << "Введіть кількість годин: ";
        cin >> godyn;
        return new PohodynnyiSluzhbovets(stavka, godyn);
    }
}

ShtatnyiSluzhbovets* stvorytyShtatnoho(bool random) {
    if (random) {
        double zarplata = 15000 + rand() % 10001;
        return new ShtatnyiSluzhbovets(zarplata);
    }
    else {
        double zarplata;
        cout << "Введіть місячну зарплату: ";
        cin >> zarplata;
        return new ShtatnyiSluzhbovets(zarplata);
    }
}

SluzhbovetsZProcentom* stvorytyProcentnoho(bool random) {
    if (random) {
        double obsiag = 50000 + rand() % 100001;
        double procent = 5 + rand() % 16;
        return new SluzhbovetsZProcentom(obsiag, procent);
    }
    else {
        double obsiag, procent;
        cout << "Введіть обсяг продажу: ";
        cin >> obsiag;
        cout << "Введіть процентну ставку: ";
        cin >> procent;
        return new SluzhbovetsZProcentom(obsiag, procent);
    }
}

int main() {
	setlocale(LC_ALL, "Ukrainian");
    srand(time(0));
    const int rozmir = 3;
    Pracivnyk* pracivnyky[rozmir];

    int vybir;
    cout << "Оберіть спосіб введення даних (1 - вручну, 2 - випадково): ";
    cin >> vybir;
    bool random = (vybir == 2);

    pracivnyky[0] = stvorytyPohodynnoho(random);
    pracivnyky[1] = stvorytyShtatnoho(random);
    pracivnyky[2] = stvorytyProcentnoho(random);

    cout << "\nІнформація про працівників:\n";
    for (int i = 0; i < rozmir; ++i) {
        pracivnyky[i]->info();
    }

    for (int i = 0; i < rozmir; ++i) {
        delete pracivnyky[i];
    }

    return 0;
}
