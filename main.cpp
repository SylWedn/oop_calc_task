#include <iostream>
#include "Calculator.h"
#include "ExpressionFormatter.h"

int main() {
    Calculator calculator;
    std::string expression;
    std::cout << "Enter expression: ";
    std::cin >> expression;
    
    std::string formattedExpression = formatExpression(expression); // Format the expression
    std::cout << "Entered line: " << expression << std::endl;
    std::cout << "Printed line: " << formattedExpression << std::endl;

    double result = calculator.calculate(expression);
    std::cout << formattedExpression << " = " << result << std::endl;

    // Wait for user input before exiting the program
    std::cin.ignore();
    std::cin.get();
    return 0;
}
