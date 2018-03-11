#ifndef __TFT_H_INCLUDED__
#define __TFT_H_INCLUDED__

#include <string>
#include <vector>

using namespace std;

class TFT {

    private:

        static const int MAXCHILDREN = 5;
        static const int MAXVALUES = MAXCHILDREN - 1;

        struct SubNode {
            string word;
            int count;

            SubNode(string word) : word = word; count = 1;
        };

        struct Node {
            //use vectors instead
            vector<struct SubNode> *words;
            vector<struct Node> *children;
            bool isLeaf;

            Node(string word, bool leafStatus) : words.push(new SubNode(word)); 
                                isLeaf = leafStatus;
                                children.push(NULL);
                                children.push(NULL);

        };

        struct Node *root;

        int nodeCount;



    public:

        TFT(void);

        ~TFT();
        void destroyRecursive(Node *node);

        void search(string word);
        void search(string word, Node *root);

        //function the returns truth statement if node has max children or not
        bool hasMaxChildren();

        void insert(string word);
        void insertNonFull(string word);
        void splitChild(string word, Node *node);
};

#endif