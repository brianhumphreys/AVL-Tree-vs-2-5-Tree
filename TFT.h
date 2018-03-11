#ifndef __TFT_H_INCLUDED__
#define __TFT_H_INCLUDED__

#include <vector>
#include <string>

using namespace std;

class TFT {

    private:

        static const int MAXCHILDREN = 5;
        static const int MAXVALUES = MAXCHILDREN - 1;

        struct SubNode {
            string word;
            int count;
        };

        struct Node {
            //use vectors instead
            std::vector<struct SubNode> *words;
            std::vector<struct Node> *children;

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

        struct Node* deleteOne(string word);
        struct Node* deleteOne(Node *ptr, string word);
};

#endif