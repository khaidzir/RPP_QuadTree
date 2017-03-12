#include "QGraph.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

QGraph::QGraph() {
    //ctor
    arraySize = 0;
    arrayNode = NULL;
}

QGraph::~QGraph() {
    //dtor
    delete [] arrayNode;
}

QGraph::QGraph(const QGraph& other) {
    arraySize = other.arraySize;
    // if (arrayNode != NULL) delete [] arrayNode;
    arrayNode = new int[arraySize];
    for(int i=0; i<arraySize; i++) {
        arrayNode[i] = other.arrayNode[i];
    }
}

QGraph& QGraph::operator=(const QGraph& other) {
    arraySize = other.arraySize;
    // if (arrayNode != NULL) delete [] arrayNode;
    arrayNode = new int[arraySize];
    for(int i=0; i<arraySize; i++) {
        arrayNode[i] = other.arrayNode[i];
    }
    return *this;
}

int QGraph::getArraySize() {
    return arraySize;
}

int QGraph::getVertexSize() {
    return arraySize/5;
}

int* QGraph::getArrayNode() {
    return arrayNode;
}

void QGraph::readPlainText() {
    FILE * pFile;
    pFile = fopen("data/plain/qgraph.txt", "r");
    int size, node;
    fscanf(pFile, "%d", &size);

    arraySize = size*5;
    arrayNode = new int[arraySize];
    int counter = 1;
    for(int i=0; i<arraySize; i++) {
        arrayNode[i] = counter;
        i++;
        for(int j=0; j<4; j++) {
            fscanf(pFile, "%d", &node);
            if (node != 0) {
                arrayNode[i] = (node-1)*5;
            } else {
                arrayNode[i] = -1;
            }
            i++;
        }
        i--;
        counter++;
    }

    fclose(pFile);
}

void QGraph::readBinary() {
    // Baca binary file
    FILE *pFile;
    long filelen;

    pFile = fopen("data/bin/qgraph.bin", "rb");
    fseek(pFile, 0, SEEK_END);
    filelen = ftell(pFile);
    rewind(pFile);

    arrayNode = (int*)malloc((filelen/4)*sizeof(int));
    fread(arrayNode, 4, filelen/4, pFile);
    fclose(pFile);

    arraySize = filelen/4;
    for(int i=0; i<arraySize; i++) {
        if (i%5 != 0 && arrayNode[i] != -1) arrayNode[i] /= 4;
    }
}

void QGraph::saveToBinary() {
    FILE * pFile;
    pFile = fopen("data/bin/qgraph.bin", "wb");

    if (arrayNode == NULL) return;
    int arraytemp[arraySize];
    for(int i=0; i<arraySize; i++) {
        if (i%5 != 0) {
            if (arrayNode[i] != -1) {
                arraytemp[i] = 4*arrayNode[i];
            } else { arraytemp[i] = arrayNode[i];
            }
        } else arraytemp[i] = arrayNode[i];
    }

    fwrite(arraytemp, sizeof(int), arraySize, pFile);
    fclose(pFile);
}

