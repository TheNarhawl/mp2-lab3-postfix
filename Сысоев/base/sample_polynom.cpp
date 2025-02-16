#include <iostream>
#include <string>
#include <polynom.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Polynom p1("5xy^2-6y+3z");
    std::cout << "Полином 1: ";
    p1.print();

    Polynom p2("2x^2+4y-z");
    std::cout << "Полином 2: ";
    p2.print();

    Polynom sum = p1 + p2;
    Polynom diff = p1 - p2;

    std::cout << "Сумма: ";
    sum.print();

    std::cout << "Разность: ";
    diff.print();

    p1.printTable();

    while (1) {
        std::string input;
        std::cout << "Введите полином: " << endl;
        std::getline(std::cin, input);
        Polynom polynom(input);

        polynom.printTable();

        Polynom sum = p1 + polynom;
        sum.print();
    }


}