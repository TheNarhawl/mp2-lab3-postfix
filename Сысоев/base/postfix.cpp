#include "postfix.h"
#include "TStack.h"

const std::map<char, int> Postfix::priority = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3}
};
Postfix::Postfix(std::string infixString)
{
    infix = infixString;

    if (infixString.empty())
        throw std::invalid_argument("Expression is empty");

    if (!bracketsAreCorrect())
        throw std::invalid_argument("Brackets are incorrect");

    convertToPostfix();
}
bool Postfix::bracketsAreCorrect() const
{
    TStack<char> stack;
    for (const auto& c : infix)
    {
        if (c == '(')
            stack.push(c);
        else if (c == ')')
        {
            if (stack.empty())
                return false;
            else
                stack.pop();
        }
    }

    return stack.empty();
}
std::string Postfix::getInfix()
{
    return infix;
}
std::string Postfix::getPostfix()
{
    return postfix;
}
std::string Postfix::convertToPostfix()
{
    for (const auto c : infix)
    {
        lexems.push_back(c);
    }

    TStack<char> stack;
    for (const auto c : lexems)
    {
        if (isalnum(c))
        {
            postfix += c;
            operands.insert({ c, 0.0 });
        }
        else if (c == '(')
        {
            stack.push(c);
        }
        else if (c == ')')
        {
            while (!stack.empty() && stack.back() != '(')
            {
                postfix += stack.back();
                stack.pop();
            }
            stack.pop();
        }
        else {
            while (!stack.empty() && stack.back() != '(' &&
                priority.at(c) < priority.at(stack.back()))
            {
                postfix += stack.back();
                stack.pop();
            }
            stack.push(c);
        }
    }
    while (!stack.empty())
    {
        postfix += stack.back();
        stack.pop();
    }

    return postfix;
}
double Postfix::calculate(const std::map<char, double>& values)
{
    for (const auto& v : values)
    {
        if (operands.find(v.first) != operands.end())
        {
            operands[v.first] = v.second;
        }
    }
    TStack<double> temp_stack;
    double leftOperand, rightOperand;

    for (char symbol : postfix)
    {
        switch (symbol)
        {
        case '+':
            rightOperand = temp_stack.back();
            temp_stack.pop();

            leftOperand = temp_stack.back();
            temp_stack.pop();

            temp_stack.push(leftOperand + rightOperand);
            break;
        case '-':
            rightOperand = temp_stack.back();
            temp_stack.pop();

            leftOperand = temp_stack.back();
            temp_stack.pop();

            temp_stack.push(leftOperand - rightOperand);
            break;
        case '*':
            rightOperand = temp_stack.back();
            temp_stack.pop();

            leftOperand = temp_stack.back();
            temp_stack.pop();

            temp_stack.push(leftOperand * rightOperand);
            break;
        case '/':
            rightOperand = temp_stack.back();
            temp_stack.pop();

            leftOperand = temp_stack.back();
            temp_stack.pop();

            temp_stack.push(leftOperand / rightOperand);
            break;
        case '^':
            rightOperand = temp_stack.back();
            temp_stack.pop();

            leftOperand = temp_stack.back();
            temp_stack.pop();

            temp_stack.push(pow(leftOperand, rightOperand));
            break;
        default:
            temp_stack.push(operands[symbol]);
            break;
        }
    }
    auto res = temp_stack.back();
    temp_stack.pop();
    return res;
}
