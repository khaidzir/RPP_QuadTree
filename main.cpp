#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "struktur_data/peta/QGraph.h"
#include "struktur_data/peta/ArrayStack.h"
#include "struktur_data/peta/GeoMap.h"
#include "struktur_data/kamus/ListVocab.h"

void coba() {
    QGraph qGraph;
    qGraph.readPlainText();
    qGraph.saveToBinary();
    qGraph.readBinary();

    GeoMap gm;
    gm.setQGraph(qGraph);

    int start, end;
    cout << "Masukkan node start dan node end : ";
    cin >> start >> end;

    while(start != -1 && end != -1) {
        int size;
        // int * path = gm.findPath(start, end, &size);
        // cout << "Path : ";
        // for(int i=0; i<size; i++) {
        //     cout << path[i] << " ";
        // }
        gm.findAllPaths(start, end);
        cout << endl << endl;

        // delete [] path;

        cout << "Masukkan node start dan node end : ";
        cin >> start >> end;
    }
}

void coba1() {
    // Load graf
    QGraph qGraph;
    qGraph.readPlainText();
    qGraph.saveToBinary();
    qGraph.readBinary();

    // Load daftar nama node
    ListVocab lv;
    lv.loadKamus();

    // GeoMap
    GeoMap gm;
    gm.setQGraph(qGraph);
    gm.setNodeNames(&lv);
    gm.loadStreetNames();

    string start, end;
    int idstart, idend;
    cout << "Masukkan node start dan node end : ";    
    cin >> start >> end; 
    idstart = gm.getNodeId(start.c_str());
    idend = gm.getNodeId(end.c_str());

    while(idstart != -1 && idend != -1) {
        int size;
        gm.findAllPaths(idstart, idend);
        cout << endl << endl;

        // delete [] path;

        cout << "Masukkan node start dan node end : ";
        cin >> start >> end;    
        idstart = gm.getNodeId(start.c_str());
        idend = gm.getNodeId(end.c_str());
    }
}

int main() {
    coba1();

    return 0;
}

