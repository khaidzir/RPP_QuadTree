#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "struktur_data/QGraph.h"
#include "struktur_data/ArrayStack.h"
#include "struktur_data/GeoMap.h"

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

int main() {
    coba();

    return 0;
}

