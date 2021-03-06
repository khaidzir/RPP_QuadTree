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
        bool empty();
        int getSize();
        int getMaxSize();
        int getItem(int idx);
        bool isExist(int e);
    protected:

    private:
        int maxSize;
        int * arrStack;
        int idx;
};

#endif // ARRAYSTACK_H
