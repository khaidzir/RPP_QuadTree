#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H


class ArrayStack
{
    public:
        ArrayStack(int msize);
        ~ArrayStack();
        ArrayStack(const ArrayStack& other);
        ArrayStack& operator=(const ArrayStack& other);


        void push(int e);
        int top();
        void pop();
        bool isEmpty();
        int getSize();
        int getMaxSize();
    protected:

    private:
        int maxSize;
        int * arrStack;
        int idx;
};

#endif // ARRAYSTACK_H
