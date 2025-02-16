#include "polynom.h"

Polynom::Polynom(const std::string& expression) {
    *this = parse(expression);
}

void Polynom::addMonomial(const Monomial& monomial) {
    terms.push_back(monomial);
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result = *this;
    for (const auto& term : other.terms) {
        result.addMonomial(term);
    }
    result.simplify();
    return result;
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result = *this;
    for (const auto& term : other.terms) {
        Monomial negativeTerm = term;
        for (auto& var : negativeTerm.variables) {
            var.second.first *= -1;
        }
        result.addMonomial(negativeTerm);
    }
    result.simplify();
    return result;
}

void Polynom::simplify() {
    std::map<std::string, double> simplified; // контейнер для объединения термов

    for (const auto& term : terms) {
        std::string key;
        for (const auto& var : term.variables) {
            key += var.first;
            if (var.second.second != 1) {
                key += "^" + std::to_string(var.second.second);
            }
        }
        simplified[key] += term.variables.begin()->second.first;
    }

    // перезапись термов
    terms.clear();
    for (const auto& entry : simplified) {
        const std::string& key = entry.first;
        double coeff = entry.second;

        if (coeff != 0) {
            Monomial newTerm;
            std::regex varRegex(R"(([a-zA-Z])\^?(\d*))");
            std::string remainingKey = key;

            std::smatch varMatches;
            while (std::regex_search(remainingKey, varMatches, varRegex)) {
                char var = varMatches[1].str()[0];
                int exp = varMatches[2].str().empty() ? 1 : std::stoi(varMatches[2].str());
                newTerm.variables[var] = { coeff, exp };
                remainingKey = varMatches.suffix().str();
            }

            terms.push_back(newTerm);
        }
    }
}

void Polynom::print() const {
    for (size_t i = 0; i < terms.size(); ++i) {
        const auto& term = terms[i];

        if (term.variables.begin()->second.first != 1 || term.variables.empty()) {
            std::cout << term.variables.begin()->second.first;
        }

        for (const auto& var : term.variables) {
            std::cout << var.first;
            if (var.second.second != 1) {
                std::cout << "^" << var.second.second;
            }
        }

        if (i < terms.size() - 1 && terms[i + 1].variables.begin()->second.first > 0) {
            std::cout << "+";
        }
    }
    std::cout << std::endl;
}


//Polynom Polynom::parse(const std::string& expression) {
//    Polynom poly;
//    /* 
//    regular espression 
//    [+-]? - знак коэффициента 
//    \d* - ноль или более цифр (целая часть кэффициента)
//    \.? - опциональная десятичная точка
//    \d* - дробная часть коэффициента
//    [a-zA-Z] - переменная
//    \^* - овциональный знак степени переменной
//    \d* - целое число степени
//    * - входная группа выражения может повторяться (несколько термов)
//    */
//    std::regex termRegex(R"(([+-]?\d*\.?\d*)([a-zA-Z]\^*\d*)*)");
//    std::smatch matches;
//    std::string remainingExpression = expression;
//
//    while (std::regex_search(remainingExpression, matches, termRegex)) {
//        if (matches.str().empty()) {
//            remainingExpression = matches.suffix().str();
//            continue;
//        }
//
//        /*std::cout << "Терм: " << matches.str() << std::endl;*/
//
//        double coefficient = matches[1].str().empty() || matches[1].str() == "+" ? 1 :
//            matches[1].str() == "-" ? -1 : std::stod(matches[1].str());
//
//        std::map<char, std::pair<double, int>> variables;
//        std::string vars = matches[2].str();
//        std::regex varRegex(R"(([a-zA-Z])\^?(\d*))");
//        std::smatch varMatches;
//
//        while (std::regex_search(vars, varMatches, varRegex)) {
//            char var = varMatches[1].str()[0];
//            int exp = varMatches[2].str().empty() ? 1 : std::stoi(varMatches[2].str());
//            variables[var] = { coefficient, exp };
//            vars = varMatches.suffix().str();
//        }
//
//        poly.addMonomial({ variables });
//
//        remainingExpression = matches.suffix().str();
//
//        if (remainingExpression.empty()) {
//            break;
//        }
//    }
//
//    return poly;
//}

Polynom Polynom::parse(const std::string& expression) {
    Polynom poly;

    /*
        regular espression
        [+-]? - знак коэффициента
        \d* - ноль или более цифр (целая часть кэффициента)
        \.? - опциональная десятичная точка
        \d* - дробная часть коэффициента
        [a-zA-Z] - переменная
        \^* - овциональный знак степени переменной
        \d* - целое число степени
        * - входная группа выражения может повторяться (несколько термов)
    */

    std::regex termRegex(R"(([+-]?\d*\.?\d*)([a-zA-Z][a-zA-Z0-9\^]*)*)");
    std::smatch matches;
    std::string remainingExpression = expression;

    while (std::regex_search(remainingExpression, matches, termRegex)) {
        if (matches.str().empty()) {
            remainingExpression = matches.suffix().str();
            continue;
        }

        /*std::cout << "Терм: " << matches.str() << std::endl;*/

        double coefficient = matches[1].str().empty() || matches[1].str() == "+" ? 1 :
            matches[1].str() == "-" ? -1 : std::stod(matches[1].str());

        std::map<char, int> variables;
        std::string vars = matches[2].str();
        std::regex varRegex(R"(([a-zA-Z])\^?(\d*))");
        std::smatch varMatches;

        while (std::regex_search(vars, varMatches, varRegex)) {
            char var = varMatches[1].str()[0];
            int exp = varMatches[2].str().empty() ? 1 : std::stoi(varMatches[2].str());
            variables[var] += exp;
            vars = varMatches.suffix().str();
        }

        poly.addMonomial({ coefficient, variables });
        remainingExpression = matches.suffix().str();

        if (remainingExpression.empty()) {
            break;
        }
    }

    return poly;
}

void Polynom::printTable() const {
    std::cout << "-----------------------------------" << endl;
    std::cout << "Коэффициент | Переменная | Степень" << endl;

    for (const auto& term : terms) {
        for (const auto& var : term.variables) {
            cout << setw(6) << var.second.first << setw(14) << var.first << setw(10) << var.second.second << endl;
        }
    }

    std::cout << "-----------------------------------" << endl;

}
