#include "GeoMap.h"
#include "ArrayStack.h"
#include <iostream>
using namespace std;

GeoMap::GeoMap() {

}

GeoMap::~GeoMap() {

}

GeoMap::GeoMap(const GeoMap& other) {
    this->qGraph = other.qGraph;
}

void GeoMap::setQGraph(QGraph qGraph) {
    this->qGraph = qGraph;
}

int* GeoMap::findPath(int start, int end, int * size) {
    int* arrayNode = qGraph.getArrayNode();
    int n = qGraph.getVertexSize();
    int narr = qGraph.getArraySize();
    int * ret;

    // Cek apakah start & end ada dalam arrayNode
    bool cekstart=false, cekend=false;
    int startidx;

    for(int i=0; ( (i<narr) && !(cekstart && cekend) ); i+=5) {
        if (start == arrayNode[i]) {
            cekstart=true;
            startidx = i;
        }
        if (end == arrayNode[i]) cekend = true;
    }

    // Jika start atau end tidak ada dalam arrayNode
    if ( !(cekstart && cekend) ) {
        *size = 0;
        return NULL;
    }

    // Jika start == end
    if (start == end) {
        ret = new int[1];
        ret[0] = start;
        *size = 1;
        return ret;
    }

    bool flag[n];
    for(int i=0; i<n; i++) flag[i] = false;
    ArrayStack pathStack(n), prevStack(n), globalStack(n);
    flag[arrayNode[startidx]-1] = true;

    // Cek apakah memiliki tetangga tujuan atau tetangga
    // yang tidak buntu
    int idx, counter=0;
    bool buntu;
    for(int i=startidx+1; i<=startidx+4; i++) {
        idx = arrayNode[i];

        // Memiliki tetangga
        if (idx != -1) {
            // Tetangga merupakan tujuan
            if (arrayNode[idx] == end) {
                *size = 2;
                ret = new int[*size];
                ret[0] = start;
                ret[1] = end;
                return ret;
            } else {
                // Cek apakah tetangga buntu
                buntu = true;
                for(int j=idx+1; j<=idx+4&&buntu; j++) {
                    if (arrayNode[j] != -1) {
                        buntu = false;
                    }
                }
                // Tetangga tidak buntu
                if (!buntu) {
                    counter++;
                    prevStack.push(start);
                    globalStack.push(idx);
                }
            }
        }
    }

    if (counter == 0) {
        *size = 0;
        return NULL;
    }

    int node, prevNode;
    int addr;
    bool found = false;
    while(!found && !globalStack.empty()) {
        // cout << globalStack.top() << endl;
        idx = globalStack.top();
        globalStack.pop();
        node = arrayNode[idx];
        // prevNode = prevStack.top();
        prevStack.pop();
        flag[arrayNode[idx]-1] = true;

        // Cek apakah memiliki tetangga==end atau memiliki
        // tetangga tidak buntu
        counter = 0;
        for(int i=idx+1; i<=idx+4; i++) {
            addr = arrayNode[i];

            // Memiliki tetangga dan belum pernah dikunjungi
            if (addr != -1 && !flag[arrayNode[addr]-1]) {
                // Tetangga merupakan tujuan
                if (arrayNode[addr] == end) {
                    counter++;
                    found = true;
                    break;
                } else {
                    // Cek apakah tetangga buntu atau sudah dikunjungi
                    buntu = true;
                    for(int j=addr+1; j<=addr+4&&buntu; j++) {
                        buntu = arrayNode[j] == -1;
                    }
                    // Tetangga tidak buntu
                    if (!buntu) {
                        counter++;
                        prevStack.push(node);
                        globalStack.push(addr);
                    }
                }
            }
        }

        if (counter > 0) pathStack.push(node);
        else {
            if (prevStack.top() == start) {
                while(!pathStack.empty()) pathStack.pop();
            } else {
                while(prevStack.top() != pathStack.top()) {
                    pathStack.pop();
                }
            }
        }
    }

    // Tidak ada jalur
    if (!found) {
        *size = 0;
        return NULL;
    }

    *size = pathStack.getSize();
    ret = new int[*size+2];
    ret[0] = start;
    for(int j=0; j<*size; j++) {
        ret[j+1] = pathStack.getItem(j);
    }
    ret[*size+1] = end;
    *size += 2;
    return ret;
}

void GeoMap::findAllPaths(int start, int end) {
    int* arrayNode = qGraph.getArrayNode();
    int n = qGraph.getVertexSize();
    int narr = qGraph.getArraySize();

    // Cek apakah start & end ada dalam arrayNode
    bool cekstart=false, cekend=false;
    int startidx;

    for(int i=0; ( (i<narr) && !(cekstart && cekend) ); i+=5) {
        if (start == arrayNode[i]) {
            cekstart=true;
            startidx = i;
        }
        if (end == arrayNode[i]) cekend = true;
    }

    // Jika start atau end tidak ada dalam arrayNode
    if ( !(cekstart && cekend) ) {
        cout << "start/end tidak ada dalam node\n";
        return;
    }

    // Jika start == end
    if (start == end) {
        cout << start << endl;
        return;
    }

    ArrayStack pathStack(n), prevStack(n), globalStack(n);

    // Cek apakah memiliki tetangga tujuan atau tetangga
    // yang tidak buntu
    int idx, counter=0;
    bool buntu;
    for(int i=startidx+1; i<=startidx+4; i++) {
        idx = arrayNode[i];

        // Memiliki tetangga
        if (idx != -1) {
            // Tetangga merupakan tujuan
            if (arrayNode[idx] == end) {
                cout << start << "-" << end << endl;
            } else {
                // Cek apakah tetangga buntu
                buntu = true;
                for(int j=idx+1; j<=idx+4&&buntu; j++) {
                    if (arrayNode[j] != -1) {
                        buntu = false;
                    }
                }
                // Tetangga tidak buntu
                if (!buntu) {
                    counter++;
                    prevStack.push(start);
                    globalStack.push(idx);
                }
            }
        }
    }

    if (counter == 0) {
        return;
    }

    int node, prevNode;
    int addr;
    while(!globalStack.empty()) {
        // cout << globalStack.top() << endl;
        idx = globalStack.top();
        globalStack.pop();
        node = arrayNode[idx];
        prevNode = prevStack.top();
        prevStack.pop();

        // Cek apakah memiliki tetangga==end atau memiliki
        // tetangga tidak buntu
        counter = 0;
        for(int i=idx+1; i<=idx+4; i++) {
            addr = arrayNode[i];

            // Memiliki tetangga dan belum ada dalam path
            if (addr != -1 && !pathStack.isExist(arrayNode[addr])
                && arrayNode[addr] != start) {
                // Tetangga merupakan tujuan
                if (arrayNode[addr] == end) {
                    cout << start << "-";
                    for(int j=0; j<pathStack.getSize(); j++) {
                        cout << pathStack.getItem(j) << "-";
                    }
                    cout << node << "-" << end << endl;
                } else {
                    // Cek apakah tetangga buntu
                    buntu = true;
                    for(int j=addr+1; j<=addr+4&&buntu; j++) {
                        buntu = arrayNode[j] == -1;
                    }
                    // Tetangga tidak buntu
                    if (!buntu) {
                        counter++;
                        prevStack.push(node);
                        globalStack.push(addr);
                    }
                }
            }
        }

        if (counter > 0) pathStack.push(node);
        else {
            if (prevStack.top() == start) {
                while(!pathStack.empty()) pathStack.pop();
            } else {
                while(prevStack.top() != pathStack.top()) {
                    pathStack.pop();
                }
            }
        }
    }

}
