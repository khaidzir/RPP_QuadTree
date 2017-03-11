#include "QTree.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

QTree::QTree() {
    //ctor
    arraySize = 0;
    arrayNode = NULL;
}

QTree::~QTree() {
    //dtor
    delete [] arrayNode;
}

QTree::QTree(const QTree& other) {
    arraySize = other.arraySize;
    if (arrayNode != NULL) delete [] arrayNode;
    arrayNode = new int[arraySize];
    for(int i=0; i<arraySize; i++) {
        arrayNode[i] = other.arrayNode[i];
    }
}

QTree& QTree::operator=(const QTree& other) {
    arraySize = other.arraySize;
    if (arrayNode != NULL) delete [] arrayNode;
    arrayNode = new int[arraySize];
    for(int i=0; i<arraySize; i++) {
        arrayNode[i] = other.arrayNode[i];
    }
    return *this;
}

void QTree::readPlainText() {
    FILE * pFile;
    pFile = fopen("data/dataplain.txt", "r");
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

void QTree::readBinary() {
    // Baca binary file
    FILE *pFile;
    long filelen;

    pFile = fopen("data/data.bin", "rb");
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

void QTree::saveToBinary() {
    FILE * pFile;
    pFile = fopen("data/data.bin", "wb");

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

