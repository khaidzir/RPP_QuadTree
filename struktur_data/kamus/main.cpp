#include "Kata.h"
#include "ListVocab.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <queue>
using namespace std;

void tes2() {
    ListVocab lv;
    lv.addWord("amat", "very");
    lv.addWord("babu", "dust");
    lv.addWord("acar", "acar");
//    cout << lv.searchWord("amat") << endl;
//    cout << lv.searchWord("abu") << endl;
//    cout << lv.searchWord("acar") << endl;
    lv.searchWord("acar");
    lv.dumpTree();
//    lv.readDumpedTree();
}

void tes3() {
    ListVocab lv;
    lv.readDumpedTree();
    lv.searchWord("acar");
    lv.searchWord("babu");
    lv.searchWord("amat");
}


ListVocab listVocab;

void showMenu();
void run();
void loadKamus();
void addKata();
void deleteKata();
void showListKata();
void showInfo();
void wrongChoice();
void exit();
void readBinary();
void saveBinary();
void searchWord();
void tes(char* in) {
    char* other = in;
    printf("%s\n", other);
}

int main() {

    run();

    return 0;
}

void showMenu() {
    printf("[1] Load kamus\n");
    printf("[2] Baca data binary\n");
    printf("[3] Tambahkan kata\n");
    printf("[4] Cari kata\n");
    printf("[5] Simpan ke file binary\n");
    printf("[6] Keluar\n");
}
void run() {
    int choice;
    showMenu();
    scanf("%d", &choice);
    while(choice != 6) {
        if (choice == 1) loadKamus();
        else if (choice == 2) readBinary();
        else if (choice == 3) addKata();
        else if (choice == 4) searchWord();
        else if (choice == 5) saveBinary();
        else if (choice == 6);
        else wrongChoice();
        showMenu();
        scanf("%d", &choice);
    }
    exit();
}
void loadKamus() {
    listVocab.loadKamus();
    cout << "Selesai\n\n";
}

void addKata() {
    string s;
    cout << "Masukkan kata yang akan ditambahkan: ";
    cin >> s;
    listVocab.addWord(s.c_str(), "");
}

void readBinary() {
    listVocab.readDumpedTree();
    cout << "Selesai\n\n";
}
void saveBinary() {
    listVocab.dumpTree();
    cout << "Selesai\n\n";
}
void searchWord() {
    string s;
    cout << "Masukkan kata yang akan dicari: ";
    cin >> s;
    listVocab.searchWord(s.c_str());
}
void deleteKata() {

}
void showListKata() {

}
void showInfo() {

}
void wrongChoice() {
    cout << "Pilihan salah!\n";
}
void exit() {

}
