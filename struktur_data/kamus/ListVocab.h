#ifndef LISTVOCAB_H
#define LISTVOCAB_H

#include "VNode.h"

class ListVocab {
    public:
        VNode* first;
        int size;
        ListVocab();
        ListVocab(const ListVocab& other);
        ListVocab& operator=(const ListVocab& other);
        ~ListVocab();

        void addWord(const char * word, char * def);
        char* searchWord(const char* word);
        void dumpTree();
        void readDumpedTree();
        void loadKamus();

    protected:

    private:
        char notfound[4];
        void freeNode(VNode* v);
        int takeIntFromByte(char * buffer, int offset);
};

#endif // LISTVOCAB_H
