#ifndef VNODE_H
#define VNODE_H

class VNode {
    public:
        char info;
        char* def;
        VNode* left;
        VNode* right;
        VNode();
        VNode(char ch);
        VNode(const VNode& other);
        VNode& operator=(const VNode& other);
        ~VNode();
        void print();

    protected:

    private:
};

#endif // VNODE_H
