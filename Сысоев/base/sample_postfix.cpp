#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    string expression = "c*(a+b)";
    Postfix postfix(expression);
    map<char, double> values = {
        {'a', 1},
        {'b', 2},
        {'c', 4},
        {'d', -2},
        {'e', -1},
        {'f', 0}
    };

    double result;

    result = postfix.calculate(values);
    cout << "Арифметическое выражение: " << postfix.getInfix() << endl;
    cout << "Постфиксная форма выражения: " << postfix.getPostfix() << endl;
    cout << "Результат: " << result << endl;

    return 0;
}
