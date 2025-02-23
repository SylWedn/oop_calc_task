#ifndef SUM_H
#define SUM_H

#include "INode.h"


class Sum : public INode {
public:
    Sum(INode* left, INode* right) : left_(left), right_(right) {}
    void print() const override {
        left_->print();
        std::cout << " + ";
        right_->print();
    }
    double calc() const override {
        return left_->calc() + right_->calc();
    }

private:
    INode* left_;
    INode* right_;
};

#endif // SUM_H
