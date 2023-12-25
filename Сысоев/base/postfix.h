#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include "TStack.h"

#include <string>
#include <map>
#include <cmath>

using namespace std;

class Postfix
{
private:
	string infix;
	string postfix;

    vector<char> lexems;
    map<char, double> operands;
    static const map<char, int> priority;

    bool bracketsAreCorrect() const;
	string convertToPostfix();

public:
	Postfix() = delete;
    Postfix(std::string infix);
	string getInfix();
	string getPostfix();
	double calculate(const map<char, double>& vals);
};

#endif
