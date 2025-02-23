#ifndef SUBTRACT_H
#define SUBTRACT_H

#include "INode.h"


class Subtract : public INode {
public:
    Subtract(INode* left, INode* right) : left_(left), right_(right) {}
    void print() const override {
        left_->print();
        std::cout << " - ";
        right_->print();
    }
    double calc() const override {
        return left_->calc() - right_->calc();
    }

private:
    INode* left_;
    INode* right_;
};

#endif // SUBTRACT_H
