#ifndef VALUE_H
#define VALUE_H

#include "INode.h"

// Класс Value, представляющий числовое значение
class Value : public INode {
public:
    Value(double value) : value_(value) {}
    void print() const override { std::cout << value_; }
    double calc() const override { return value_; }

private:
    double value_;  // Переменная для хранения значения
};

#endif // VALUE_H
