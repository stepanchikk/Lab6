#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ======== Невіртуальне успадкування ========
namespace NonVirtual {
    class A {
    protected:
        int a;
    public:
        A() : a(0) {
            cout << "Створено об'єкт NonVirtual::A" << endl;
        }
        ~A() {
            cout << "Знищено об'єкт NonVirtual::A" << endl;
        }
        void input(bool randomize) {
            if (randomize) a = rand() % 100;
            else {
                cout << "NonVirtual::A -> Введіть a: ";
                cin >> a;
            }
        }
        void print() const {
            cout << "a = " << a << endl;
        }
    };

    class B : public A {
    protected:
        int b;
    public:
        B() : b(0) {
            cout << "Створено об'єкт NonVirtual::B" << endl;
        }
        ~B() {
            cout << "Знищено об'єкт NonVirtual::B" << endl;
        }
        void input(bool randomize) {
            A::input(randomize);
            if (randomize) b = rand() % 100;
            else {
                cout << "NonVirtual::B -> Введіть b: ";
                cin >> b;
            }
        }
        void print() const {
            A::print();
            cout << "b = " << b << endl;
        }
    };

    class C : public A {
    protected:
        int c;
    public:
        C() : c(0) {
            cout << "Створено об'єкт NonVirtual::C" << endl;
        }
        ~C() {
            cout << "Знищено об'єкт NonVirtual::C" << endl;
        }
        void input(bool randomize) {
            A::input(randomize);
            if (randomize) c = rand() % 100;
            else {
                cout << "NonVirtual::C -> Введіть c: ";
                cin >> c;
            }
        }
        void print() const {
            A::print();
            cout << "c = " << c << endl;
        }
    };

    class D : public B, public C {
        int d;
    public:
        D() : d(0) {
            cout << "Створено об'єкт NonVirtual::D" << endl;
        }
        ~D() {
            cout << "Знищено об'єкт NonVirtual::D" << endl;
        }
        void input(bool randomize) {
            B::input(randomize);
            C::input(randomize);
            if (randomize) d = rand() % 100;
            else {
                cout << "NonVirtual::D -> Введіть d: ";
                cin >> d;
            }
        }
        void print() const {
            B::print();
            C::print();
            cout << "d = " << d << endl;
        }
    };
}

// ======== Віртуальне успадкування ========
namespace Virtual {
    class A {
    protected:
        int a;
    public:
        A() : a(0) {
            cout << "Створено об'єкт Virtual::A" << endl;
        }
        ~A() {
            cout << "Знищено об'єкт Virtual::A" << endl;
        }
        void input(bool randomize) {
            if (randomize) a = rand() % 100;
            else {
                cout << "Virtual::A -> Введіть a: ";
                cin >> a;
            }
        }
        void print() const {
            cout << "a = " << a << endl;
        }
    };

    class B : virtual public A {
    protected:
        int b;
    public:
        B() : b(0) {
            cout << "Створено об'єкт Virtual::B" << endl;
        }
        ~B() {
            cout << "Знищено об'єкт Virtual::B" << endl;
        }
        void input(bool randomize) {
            if (randomize) b = rand() % 100;
            else {
                cout << "Virtual::B -> Введіть b: ";
                cin >> b;
            }
        }
        void print() const {
            cout << "b = " << b << endl;
        }
    };

    class C : virtual public A {
    protected:
        int c;
    public:
        C() : c(0) {
            cout << "Створено об'єкт Virtual::C" << endl;
        }
        ~C() {
            cout << "Знищено об'єкт Virtual::C" << endl;
        }
        void input(bool randomize) {
            if (randomize) c = rand() % 100;
            else {
                cout << "Virtual::C -> Введіть c: ";
                cin >> c;
            }
        }
        void print() const {
            cout << "c = " << c << endl;
        }
    };

    class D : public B, public C {
        int d;
    public:
        D() : d(0) {
            cout << "Створено об'єкт Virtual::D" << endl;
        }
        ~D() {
            cout << "Знищено об'єкт Virtual::D" << endl;
        }
        void input(bool randomize) {
            A::input(randomize); // лише один екземпляр A
            B::input(randomize);
            C::input(randomize);
            if (randomize) d = rand() % 100;
            else {
                cout << "Virtual::D -> Введіть d: ";
                cin >> d;
            }
        }
        void print() const {
            A::print();
            B::print();
            C::print();
            cout << "d = " << d << endl;
        }
    };
}

int main() {
	setlocale(LC_ALL, "ukr");
    srand(time(0));

    bool randomize;
    cout << "Виберіть режим введення (0 - з клавіатури, 1 - випадково): ";
    cin >> randomize;

    cout << "\n=== Створення NonVirtual::D ===\n";
    NonVirtual::D nv_obj;
    nv_obj.input(randomize);

    cout << "\n=== Створення Virtual::D ===\n";
    Virtual::D v_obj;
    v_obj.input(randomize);

    cout << "\n=== Вивід ===\n";
    cout << "\nNonVirtual::D (розмір: " << sizeof(nv_obj) << " байт):\n";
    nv_obj.print();

    cout << "\nVirtual::D (розмір: " << sizeof(v_obj) << " байт):\n";
    v_obj.print();

    cout << "\n=== Завершення програми (буде знищення об'єктів) ===\n";

    return 0;
}
