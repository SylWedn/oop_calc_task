#ifndef INODE_H
#define INODE_H

#include <iostream>

// INode interface with print and calc methods
class INode {
public:
    virtual ~INode() = default;
    virtual void print() const = 0;  
    virtual double calc() const = 0; 
};

#endif // INODE_H
