#ifndef QGRAPH_H
#define QGRAPH_H

class QGraph
{
    public:
        // ctor,cctor,dtor
        QGraph();
        ~QGraph();
        QGraph(const QGraph& other);
        QGraph& operator=(const QGraph& other);

        // getter
        int getArraySize();
        int getVertexSize();
        int* getArrayNode();

        void readPlainText();
        void readBinary();
        void saveToBinary();

    protected:

    private:
        int * arrayNode;
        int arraySize;
};

#endif // QGraph_H
