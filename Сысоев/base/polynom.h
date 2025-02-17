#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <regex>
#include <cctype>
#include <iomanip>

using namespace std;

class Polynom
{
public:
	struct Monomial {
		Monomial() = default;

		std::map<char, std::pair<double, int>> variables;

		Monomial(double coef, const std::map<char, int>& vars) {
			for (const auto& var : vars) {
				variables[var.first] = { coef, var.second };
			}
		}

		void print() const {
			for (const auto& var : variables) {
				std::cout << var.second.first << var.first << "^" << var.second.second << " ";
			}
		}

		bool operator<(const Monomial& other) const {
			return variables < other.variables;
		}
	};

	Polynom() = default;

	Polynom(const std::string& expression);

	void addMonomial(const Monomial& monomial);

	Polynom operator+(const Polynom& other) const;

	Polynom operator-(const Polynom& other) const;

	void simplify();

	void print() const;

	void printTable() const;

	static Polynom parse(const std::string& expression);


private:
	std::vector<Monomial> terms;
};

#endif