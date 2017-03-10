#ifndef QTREE_H
#define QTREE_H

#include "QNode.h"
#include <vector>
using namespace std;

class QTree
{
    public:
        int * arrayNode;
        int arraySize;
        QNode* first;
        QTree();
        ~QTree();
        void dumpTree();

        void readPlainText();
        void readBinary();
        void saveToBinary();

    protected:

    private:
        void freeNode(QNode* q);
        bool isAda(vector<int>& v, int n);
};

#endif // QTREE_H
