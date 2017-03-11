#ifndef QTREE_H
#define QTREE_H

class QTree
{
    public:
        int * arrayNode;
        int arraySize;

        QTree();
        ~QTree();
        QTree(const QTree& other);
        QTree& operator=(const QTree& other);

        void readPlainText();
        void readBinary();
        void saveToBinary();

    protected:

    private:
};

#endif // QTREE_H
