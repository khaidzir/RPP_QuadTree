#include <cstdio>
#include <cstdlib>
#include <stack>
#include <iostream>
using namespace std;

#include "QNode.h"
#include "QTree.h"
#include "ArrayStack.h"

vector<int> findPath(int * arrayNode, int start, int end, int size);

int main() {
    QTree qt;
    qt.readPlainText();
    qt.saveToBinary();
    qt.readBinary();

    int start, end;
    cout << "Masukkan node start dan node end : ";
    cin >> start >> end;

    while(start != -1 && end != -1) {
        vector<int> path = findPath(qt.arrayNode, start, end, qt.arraySize);
        cout << "Path : ";
        for(int i=0; i<path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << endl << endl;

        cout << "Masukkan node start dan node end : ";
        cin >> start >> end;
    }

    return 0;
}

vector<int> findPath(int * arrayNode, int start, int end, int size) {
    // Cek apakah start & end ada dalam arrayNode
    bool cekstart=false, cekend=false;
    int startidx;
    for(int i=0; ((i<5*size)&&(!cekstart||!cekend)); i+=5) {
        if (start == arrayNode[i]) {
            cekstart=true;
            startidx = i;
        }
        cekend = end==arrayNode[i];
    }

    // Jika start = end
    vector<int> ret;
    if (start == end) {
        ret.push_back(start);
        return ret;
    }

    bool flag[size];
    for(int i=0; i<size; i++) flag[i] = false;
    stack<int> pathStack, globalStack;
    flag[startidx] = true;
    int idx;
    for(int i=startidx+1; i<=startidx+4; i++) {
        idx = arrayNode[i];
        if (idx != -1) {
            globalStack.push(idx);
        }
    }

    int node;
    int counter;
    bool found = false;
    while(!found && !globalStack.empty()) {
        idx = globalStack.top();
        globalStack.pop();
        node = arrayNode[idx];
        if (node == end){
            found = true;
            pathStack.push(node);
        } else {
            counter=0;
            for(int i=idx+1; i<=idx+4; i++) {
                idx = arrayNode[i];
                if (idx != -1) {
                    counter++;
                    globalStack.push(idx);
                }
            }
            if (counter == 0) {
                if (!pathStack.empty()) pathStack.pop();
            } else {
                pathStack.push(node);
            }
        }
        flag[idx] = true;
    }

    while(!pathStack.empty()) {
        ret.push_back(pathStack.top());
        pathStack.pop();
    }

    int temp, n=ret.size()/2;
    for(int i=0,j=ret.size()-1; i<n; i++,j--) {
        temp = ret[i];
        ret[i] = ret[j];
        ret[j] = temp;
    }

    return ret;
}
