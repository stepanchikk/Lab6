#include <iostream>
#include <cmath>
#include <random>

class Figure {
public:
    Figure() = default;
    virtual ~Figure() { std::cout << "Знищення фігури\n"; }

    virtual void print(std::ostream& os) const = 0; // чисто віртуальна функція для виводу
    virtual void read(std::istream& is) = 0; // чисто віртуальна функція для вводу
};
};

std::ostream& operator<<(std::ostream& os, const Figure& f) {
    f.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& f) {
    f.read(is);
    return is;
}

class Circle : virtual public Figure {
protected:
    double radius;

public:
    Circle(double r = 0) : radius(r) {}
    virtual ~Circle() { std::cout << "Знищення кола\n"; }

    virtual void print(std::ostream& os) const override {
        os << "Коло: радіус = " << radius << "\n";
    }

    virtual void read(std::istream& is) override {
        std::cout << "Введіть радіус кола: ";
        is >> radius;
    }

    double getRadius() const { return radius; }
};

class Square : virtual public Figure {
protected:
    double side;

public:
    Square(double s = 0) : side(s) {}
    virtual ~Square() { std::cout << "Знищення квадрата\n"; }

    virtual void print(std::ostream& os) const override {
        os << "Квадрат: сторона = " << side << "\n";
    }

    virtual void read(std::istream& is) override {
        std::cout << "Введіть сторону квадрата: ";
        is >> side;
    }

    double getSide() const { return side; }
};

class InscribedCircle : public Circle, public Square {
public:
    // Ініціалізація базових класів через конструктори
    InscribedCircle(double s = 0)
        : Circle(s / 2.0), Square(s) {
    }

    ~InscribedCircle() override { std::cout << "Знищення вписаного кола\n"; }

    void print(std::ostream& os) const override {
        os << "Вписане коло всередині квадрата:\n";
        os << "Сторона квадрата = " << Square::getSide() << "\n";
        os << "Радіус кола = " << Circle::getRadius() << "\n";
    }

    void read(std::istream& is) override {
        std::cout << "Введіть сторону квадрата для обчислення вписаного кола: ";
        is >> Square::side;
        Circle::radius = Square::side / 2.0;
    }
};

// Функція для генерації випадкових чисел
double generateRandomNumber(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    InscribedCircle ic;
    int choice;

    std::cout << "Оберіть метод введення даних:\n";
    std::cout << "1. Введення з клавіатури\n";
    std::cout << "2. Випадкові числа\n";
    std::cout << "Вибір: ";
    std::cin >> choice;

    if (choice == 1) {
        std::cin >> ic; // Введення з клавіатури
    }
    else if (choice == 2) {
        double randomSide = generateRandomNumber(1.0, 20.0);
        std::cout << "Випадково згенерована сторона квадрата: " << randomSide << "\n";
        ic = InscribedCircle(randomSide); // Створення з випадковим значенням
    }
    else {
        std::cout << "Невірний вибір! Використано введення з клавіатури за замовчуванням.\n";
        std::cin >> ic;
    }

    std::cout << ic;  // Виведення результатів

    return 0;
}
