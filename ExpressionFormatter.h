#ifndef EXPRESSION_FORMATTER_H
#define EXPRESSION_FORMATTER_H

#include <string>
#include <stack>

// Function to determine the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to add parentheses according to operator precedence
std::string formatExpression(const std::string& expression) {
    std::stack<char> ops;
    std::stack<std::string> values;

    auto applyOperator = [&](char op) {
        std::string right = values.top();
        values.pop();
        std::string left = values.top();
        values.pop();
        values.push("(" + left + " " + op + " " + right + ")");
    };

    for (size_t i = 0; i < expression.size(); ++i) {
        char token = expression[i];
        if (isdigit(token) || isalpha(token)) {
            std::string value(1, token);
            while (i + 1 < expression.size() && (isdigit(expression[i + 1]) || expression[i + 1] == '.' || isalpha(expression[i + 1]))) {
                value += expression[++i];
            }
            values.push(value);
        } else if (token == ' ') {
            continue;
        } else if (token == '(') {
            ops.push(token);
        } else if (token == ')') {
            while (!ops.empty() && ops.top() != '(') {
                applyOperator(ops.top());
                ops.pop();
            }
            ops.pop(); // Remove the opening parenthesis '('
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                applyOperator(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }

    while (!ops.empty()) {
        applyOperator(ops.top());
        ops.pop();
    }

    return values.top();
}

#endif // EXPRESSION_FORMATTER_H