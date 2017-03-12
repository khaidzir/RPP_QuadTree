#include "ListVocab.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

ListVocab::ListVocab() {
    first = NULL;
    size = 0;
    for(int i=0; i<4; i++) {
        notfound[i] = (char)255;
    }
}

ListVocab::ListVocab(const ListVocab& other) {
    /*VNode* temp;
    while(first != NULL) {
        temp = first->next;
        delete first;
        first = temp;
    }
    this->first = other.first;
    this->size = other.size;*/
}

ListVocab& ListVocab::operator=(const ListVocab& other) {
    /*VNode* temp;
    while(first != NULL) {
        temp = first->next;
        delete first;
        first = temp;
    }
    this->first = other.first;
    this->size = other.size;*/
    return *this;
}

ListVocab::~ListVocab() {
    freeNode(first);
}

void ListVocab::freeNode(VNode* v) {
    if (v == NULL) return;
    freeNode(v->left);
    freeNode(v->right);
    delete v;
}


void ListVocab::addWord(const char * word, char * def) {
    if (word[0] == '\0') return;

//    printf("%s\n", word);

    // Pertama kali
    if (first == NULL) {
        first = new VNode(word[0]);
        int i=1;
        VNode* temp = first;
        while(word[i] != '\0') {
            temp->left = new VNode(word[i]);
            temp = temp->left;
            i++;
        }
        temp->left = new VNode('\0');
        temp = temp->left;
        temp->def = def;
        return;
    }

    // Ganti first
    if (word[0] < first->info) {
        VNode* v = new VNode(word[0]);
        int i=1;
        VNode* temp = v;
        while(word[i] != '\0') {
            temp->left = new VNode(word[i]);
            temp = temp->left;
            i++;
        }
        temp->left = new VNode('\0');
        temp = temp->left;
        temp->def = def;

        // Ganti first
        temp = first;
        first = v;
        first->right = temp;

        return;
    }

    int i=0;
    bool foundpos = false;
    int sisip = 0;
    VNode* temp = first;
    VNode* parent = first;
    VNode* ptemp;

    while(!foundpos) {
        if (temp->info == word[i]) {
            i++;
            if (temp->left == NULL) return;
            parent = temp;
            temp = temp->left;
        } else if (temp->info > word[i]) {
            sisip = parent->left == temp ? 1 : 2;
            foundpos = true;
        } else {
            if (temp->right != NULL) {
                ptemp = temp;
                temp = temp->right;
            } else foundpos = true;
        }
    }

    // Selesaikan kata baru
    VNode* v = new VNode(word[i]);
    VNode* temp3 = v;
    if (word[i] != '\0') {
        i++;
        while(word[i] != '\0') {
            temp3->left = new VNode(word[i]);
            temp3 = temp3->left;
            i++;
        }
        temp3->left = new VNode('\0');
        temp3 = temp3->left;
    }
    temp3->def = def;


    if (sisip==0) { // Tambah baru tanpa menyisip di tengah-tengah
        temp->right = v;
    } else if (sisip == 1) {    // Sisip di awal
        parent->left = v;
        v->right = temp;
    } else {    // Tambah baru dengan menyisip di tengah-tengah
        ptemp->right = v;
        v->right = temp;
    }

}

char* ListVocab::searchWord(const char* word) {
    if (first == NULL) return notfound;
    VNode* temp = first;
    int i=0;
    bool stop = false, found = false;
    while(!stop && !found) {
        printf("%c : %c\n", word[i], temp->info);
        if (word[i] < temp->info) {stop = true; printf("cek 1\n");}
        else if (word[i] > temp->info) {
            if (temp->right == NULL) {stop = true; printf("cek 2\n");}
            else temp = temp->right;
        } else {
            if (word[i] == '\0') found = true;
            else {
                if (temp->left == NULL) {stop = true; printf("cek 3\n");}
                else {
                    temp = temp->left;
                    i++;
                }
            }
        }
    }

    if (!found) return notfound;
    else return temp->def;
}

void ListVocab::dumpTree() {
    FILE * pFile;
    pFile = fopen("data/bin/node_name.bin", "wb");

    if (first == NULL) {
        fclose(pFile);
        return;
    }

    queue<VNode*> qn;
    queue<size_t> qm;
    size_t sizec = sizeof(char), sizei = sizeof(size_t), sizes = sizec+2*sizei, nol = 0;

    qn.push(first);
    qm.push(0);
    size_t freemem = sizes, mem;
    while(!qn.empty()) {
        VNode* n = qn.front();
        qn.pop();
        mem = qm.front();
        qm.pop();
        fseek(pFile, mem, SEEK_SET);
        fwrite( &(n->info), sizec, 1, pFile);
        mem+=sizec;

        if (n->left != NULL) {
            if (n->left->info != '\0') {
                fseek(pFile, mem, SEEK_SET);
                fwrite(&freemem, sizei, 1, pFile);
                qn.push(n->left);
                qm.push(freemem);
                freemem+=sizes;
            }
        } else {
            fseek(pFile, mem, SEEK_SET);
            fwrite(&nol, sizei, 1, pFile);
        }

        mem+=sizei;
        if (n->right != NULL) {
            fseek(pFile, mem, SEEK_SET);
            fwrite(&freemem, sizei, 1, pFile);
            qn.push(n->right);
            qm.push(freemem);
            freemem+=sizes;
        } else {
            fseek(pFile, mem, SEEK_SET);
            fwrite(&nol, sizei, 1, pFile);
        }
    }

    fclose(pFile);
}

void ListVocab::readDumpedTree() {
    // Hapus node sekarang
    freeNode(first);
    first = NULL;

    // Baca binary file
    FILE *pFile;
    char *buffer;
    long filelen;

    pFile = fopen("data/bin/data.bin", "rb");
    fseek(pFile, 0, SEEK_END);
    filelen = ftell(pFile);
    rewind(pFile);

    buffer = (char *)malloc(filelen*sizeof(char));
    fread(buffer, filelen, 1, pFile);
    fclose(pFile);

//    for(int i=0; i<filelen; i+=9){
//        printf("%c ", buffer[i]);
//    }
//    printf("\n");

    // Bangun tree dari array
    queue<VNode*> qn;
    queue<int> qm;
    int offset = 1;
    first = new VNode(buffer[0]);
    VNode* v = first;
    int left = takeIntFromByte(buffer, offset);
    offset += 4;
    int right = takeIntFromByte(buffer, offset);
    printf("%d --- %d\n", left, right);
    if (left != 0) {
        v->left = new VNode(buffer[left]);
        qn.push(v->left);
        qm.push(left);
    } else {
        v->left = new VNode('\0');
    }
    if (right != 0) {
        v->right = new VNode(buffer[right]);
        qn.push(v->right);
        qm.push(right);
    }

    while(!qn.empty()) {
        v = qn.front();
        qn.pop();
        offset = qm.front();
        qm.pop();
        offset++;
        left = takeIntFromByte(buffer, offset);
        offset += 4;
        right = takeIntFromByte(buffer, offset);
        printf("%d : %d\n", left, right);
        if (left != 0) {
            v->left = new VNode(buffer[left]);
            qn.push(v->left);
            qm.push(left);
        } else {
            v->left = new VNode('\0');
        }
        if (right != 0) {
            v->right = new VNode(buffer[right]);
            qn.push(v->right);
            qm.push(right);
        }
    }

}

int ListVocab::takeIntFromByte(char * buffer, int offset) {
    int ret = 0;
    for(int i=0; i<4; i++) {
        ret = ret | (buffer[i+offset] << (8*i));
    }
    return ret;
}

void ListVocab::loadKamus() {
    ifstream in("data/plain/node_name.txt");
    if (!in) {
        return;
    }

    string str;
    int id=1;
    while(getline(in, str)) {
        if (str.length() > 0) {
            char* def = new char[4];
            def[0] = (char) (((id&0xFF000000)>>24)&0xFF);
            def[1] = (char) (((id&0x00FF0000)>>16)&0xFF);
            def[2] = (char) (((id&0x0000FF00)>>8)&0xFF);
            def[3] = (char)  (id&0x000000FF);
            addWord(str.c_str(), def);
            id++;
            cout << str << " : ";
            for(int i=0; i<4; i++) cout << (int)def[i] << " ";
            cout << endl;
        }
    }

    in.close();
}
