#include "QTree.h"
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <iostream>
#include <vector>
using namespace std;

QTree::QTree() {
    //ctor
}

QTree::~QTree() {
    //dtor
//    freeNode(first);
}

void QTree::freeNode(QNode* q) {
    if (q == NULL) return;
    for(int i=0; i<4; i++) {
        freeNode(q->branches[i]);
    }
    delete q;
}

void QTree::readPlainText() {
    FILE * pFile;
    pFile = fopen("dataplain.txt", "r");
    int size, node;
    fscanf(pFile, "%d", &size);
//    QNode* arrNode[size];
//    for(int i=0; i<size; i++) {
//        arrNode[i] = new QNode();
//        arrNode[i]->info = i+1;
//    }
//
//    for(int i=0; i<size; i++) {
//        for(int j=0; j<4; j++) {
//            fscanf(pFile, "%d", &node);
//            if (node != 0) {
//                arrNode[i]->branches[j] = arrNode[node-1];
//            } else {
//                arrNode[i]->branches[j] = NULL;
//            }
//        }
//    }
//
//    first = arrNode[0];

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
//    for(int i=0; i<arraySize; i++) {
//        cout << arrayNode[i] << " ";
//    }
//    cout << endl;

    fclose(pFile);
}

void QTree::readBinary() {
    // Baca binary file
    FILE *pFile;
    long filelen;

    pFile = fopen("data.bin", "rb");
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
//    for(int i=0; i<arraySize; i++) {
//        cout << arrayNode[i] << " ";
//    }
//    cout << endl;

}

void QTree::saveToBinary() {
    FILE * pFile;
    pFile = fopen("data.bin", "wb");

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
//    for(int i=0; i<arraySize; i++) {
//        cout << arraytemp[i] << " ";
//    }
//    cout << endl;

//    if (first == NULL) {
//        fclose(pFile);
//        return;
//    }
//
//    queue<QNode*> qn;
//    queue<size_t> qm;
//    size_t sizec = sizeof(int), sizei = sizeof(size_t), sizes = sizec+4*sizei, nol = -1;
//
//    qn.push(first);
//    qm.push(0);
//    size_t freemem = sizes, mem;
//    vector<int> v;
//    v.push_back(first->info);
//    cout << "Tes 1\n";
//
//    while(!qn.empty()) {
//        QNode* n = qn.front();
//        qn.pop();
//        mem = qm.front();
//        qm.pop();
//        fseek(pFile, mem, SEEK_SET);
//        fwrite( &(n->info), sizec, 1, pFile);
//        mem+=sizec;
//
//        for(int i=0; i<4; i++) {
//            if (n->branches[i] != NULL) {
//                fseek(pFile, mem, SEEK_SET);
//                fwrite(&freemem, sizei, 1, pFile);
//                if (!isAda(v, (n->branches[i])->info)) {
//                    qn.push(n->branches[i]);
//                    qm.push(freemem);
//                    freemem+=sizes;
//                }
//            } else {
//                fseek(pFile, mem, SEEK_SET);
//                fwrite(&nol, sizei, 1, pFile);
//            }
//
//            mem+=sizei;
//        }
//    }
//
//    cout << "Tes 2\n";

    fclose(pFile);
}

bool QTree::isAda(vector<int>& v, int n) {
    bool found = false;
    for(int i=0; i<v.size()&&!found; i++) {
        if (v[i] == n) found = true;
    }
    if (!found) v.push_back(n);
    return found;
}
