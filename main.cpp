#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "struktur_data/peta/QGraph.h"
#include "struktur_data/peta/ArrayStack.h"
#include "struktur_data/peta/GeoMap.h"
#include "struktur_data/kamus/ListVocab.h"

// Variabel global
QGraph qGraph;
ListVocab lv;
GeoMap gm;

void init();
void showMenu();
void run();
void wrongChoice();
void findAllPaths();
void findAllPathsById();
void printGraph();
void exit();

int main() {
    init();
    run();

    return 0;
}

void init() {
    // Load graf
    qGraph.readPlainText();
    qGraph.saveToBinary();
    qGraph.readBinary();

    // Load daftar nama node
    lv.loadKamus();

    // Inisialisasi GeoMap
    gm.setQGraph(qGraph);
    gm.setNodeNames(&lv);
    gm.loadStreetNames();
}

void showMenu() {
    printf("[1] Cari semua jalur (nama)\n");
    printf("[2] Cari semua jalur (id)\n");
    printf("[3] Print graf\n");
    printf("[4] Keluar\n");
}

void findAllPaths() {
    string start, end;
    cout << "Masukkan nama node start dan node end : ";    
    cin >> start >> end;
    gm.findAllPaths(start.c_str(), end.c_str());
}

void findAllPathsById() {
    int start, end;
    cout << "Masukkan id node start dan node end : ";    
    cin >> start >> end;
    gm.findAllPaths(start, end);
}

void printGraph() {
    int * arr = qGraph.getArrayNode();
    int size = qGraph.getArraySize();
    for(int i=0; i<size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void wrongChoice() {
    cout << "Pilihan salah!\n";
}

void run() {
    int choice;
    showMenu();
    scanf("%d", &choice);
    while(choice != 4) {
        if (choice == 1) findAllPaths();
        else if (choice == 2) findAllPathsById();
        else if (choice == 3) printGraph();
        else wrongChoice();
        showMenu();
        scanf("%d", &choice);
    }
    exit();
}

void exit() {

}