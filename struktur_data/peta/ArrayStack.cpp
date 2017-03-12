#include <cstdlib>
#include "ArrayStack.h"

ArrayStack::ArrayStack(int msize) {
    //ctor
    this->maxSize = msize;
    arrStack = new int[maxSize];
    idx = -1;
}

ArrayStack::~ArrayStack() {
    //dtor
    delete [] arrStack;
}

ArrayStack::ArrayStack(const ArrayStack& other) {
    //copy ctor
    maxSize = other.maxSize;
    idx = other.idx;
    if (arrStack != NULL) delete [] arrStack;
    arrStack = new int[maxSize];
    for(int i=0; i<=idx; i++) {
        arrStack[i] = other.arrStack[i];
    }
}

ArrayStack& ArrayStack::operator=(const ArrayStack& other) {
    maxSize = other.maxSize;
    idx = other.idx;
    if (arrStack != NULL) delete [] arrStack;
    arrStack = new int[maxSize];
    for(int i=0; i<=idx; i++) {
        arrStack[i] = other.arrStack[i];
    }
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

bool ArrayStack::empty() {
    return idx < 0;
}

int ArrayStack::getSize() {
    if (idx >= 0) return idx+1;
    else return 0;
}

int ArrayStack::getMaxSize() {
    return maxSize;
}

int ArrayStack::getItem(int idx) {
    return arrStack[idx];
}

bool ArrayStack::isExist(int e) {
    bool found=false;
    for(int i=0; i<=idx&&!found; i++) {
        found = arrStack[i] == e;
    }
    return found;
}
