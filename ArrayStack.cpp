#include "ArrayStack.h"

ArrayStack::ArrayStack(int msize)
{
    //ctor
    this->maxSize = msize;
    arrStack = new int[maxSize];
    idx = -1;
}

ArrayStack::~ArrayStack()
{
    //dtor
    delete [] arrStack;
}

ArrayStack::ArrayStack(const ArrayStack& other)
{
    //copy ctor
}

ArrayStack& ArrayStack::operator=(const ArrayStack& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void ArrayStack::push(int e) {
    if (idx < maxSize-1) {
        idx++;
        arrStack[idx] = e;
    }
}

int ArrayStack::top() {
    return arrStack[idx];
}

void ArrayStack::pop() {
    if (idx >= 0) {
        idx--;
    }
}

bool ArrayStack::isEmpty() {
    return idx < 0;
}

int ArrayStack::getSize() {
    if (idx >= 0) return idx+1;
    else return 0;
}

int ArrayStack::getMaxSize() {
    return maxSize;
}
