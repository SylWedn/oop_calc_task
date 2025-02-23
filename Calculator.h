#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include "INode.h"
#include "Value.h"
#include "Sum.h"
#include "Subtract.h"
#include "Multiply.h"
#include "Divide.h"

class Calculator {
public:
    double calculate(const std::string& expression) {
        std::unordered_map<char, double> variables;
        INode* root = parseExpression(expression, variables);
        double result = root->calc();
        delete root;
        return result;
    }

private:
    INode* parseExpression(const std::string& expression, std::unordered_map<char, double>& variables) {
        std::stack<INode*> values;
        std::stack<char> ops;

        for (size_t i = 0; i < expression.size(); ++i) {
            char token = expression[i];
            if (isdigit(token)) {
                double value = 0;
                while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                    value = value * 10 + (expression[i] - '0');
                    ++i;
                }
                --i;  // Decrement index as it will be incremented in the loop
                values.push(new Value(value));
            } else if (token == ' ') {
                continue;
            } else if (isalpha(token)) {
                if (variables.find(token) == variables.end()) {
                    double value;
                    std::cout << "Enter value for " << token << ": ";
                    while (!(std::cin >> value)) {
                        std::cin.clear(); // Clear the input stream
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip invalid input
                        std::cout << "Invalid input. Please enter a numeric value for " << token << ": ";
                    }
                    variables[token] = value;
                }
                values.push(new Value(variables[token]));
            } else if (token == '(') {
                ops.push(token);
            } else if (token == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    performOperation(values, ops.top());
                    ops.pop();
                }
                ops.pop(); // Remove the opening parenthesis '('
            } else if (token == '+' || token == '-' || token == '*' || token == '/') {
                while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                    performOperation(values, ops.top());
                    ops.pop();
                }
                ops.push(token);
            }
        }

        while (!ops.empty()) {
            performOperation(values, ops.top());
            ops.pop();
        }

        return values.top();
    }

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    void performOperation(std::stack<INode*>& values, char op) {
        INode* right = values.top();
        values.pop();
        INode* left = values.top();
        values.pop();

        INode* result = nullptr;
        switch (op) {
            case '+': result = new Sum(left, right); break;
            case '-': result = new Subtract(left, right); break;
            case '*': result = new Multiply(left, right); break;
            case '/': result = new Divide(left, right); break;
        }
        values.push(result);
    }
};

#endif // CALCULATOR_H
