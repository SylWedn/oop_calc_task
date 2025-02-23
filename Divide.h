#ifndef DIVIDE_H
#define DIVIDE_H

#include "INode.h"
#include <stdexcept>

class Divide : public INode {
public:
    Divide(INode* left, INode* right) : left_(left), right_(right) {}
    void print() const override {
        left_->print();
        std::cout << " / ";
        right_->print();
    }
    double calc() const override {
        double rightValue = right_->calc();
        if (rightValue == 0) {
            throw std::runtime_error("Division by zero");
        }
        return left_->calc() / rightValue;
    }

private:
    INode* left_;
    INode* right_;
};

#endif // DIVIDE_H
