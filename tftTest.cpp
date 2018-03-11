#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <dirent.h>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <ctime>

using namespace std;

class AVL {

    private: 

        struct Node
		{
			//struct Node(string word) : word(word), count(0), right(NULL), left(NULL) {}

			string word;
			int count;
			struct Node *right, *left; 

            Node(string word) : word(word), count(1), right(NULL), left(NULL){}
                //word = word;
                //count = 1;
                //right = NULL;std::string
                // left = NULL;
        //}
		};

        int nodeCount;
		struct Node * root;
    
    public:
        //constructor
        AVL(void) {
            root = NULL;
            nodeCount = 0;
        }

        //destructor
	    ~AVL() {
            destroyRecursive(root);
        }
        void destroyRecursive(Node* node) {
            if (node){
                destroyRecursive(node->left);
                destroyRecursive(node->right);
                delete node;
            }
        }

        void printTree() {
            printTree(root);
        }
        void printTree(Node * root) {
            if(root != NULL) {
                printTree(root->left);
                cout << " " << root->word;
                printTree(root->right);
            }
        }

        //search functions
	    bool search(string word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            return searchHelper(root, word);
        }
        bool searchHelper(struct Node* root, string word) {
            if(root == NULL) 
                return false;
            else if (word < root->word)
                return searchHelper(root->left, word);
            else if (word > root->word)
                return searchHelper(root->right, word);
            else return true;
        }

        //utility functions
        void rotateLeft(Node* y) {

            //label the nodes to be rotated
            Node* x = y->right;
            Node* T = x->left;

            //rotate the nodes
            x->left = y;
            y->right = T;

            //If there was a height variable in the Node then we would 
            //recalculate height here...

            return;

        }
        void rotateRight(Node* y) {
            //label the nodes to be rotated
            Node* x = y->left;
            Node* T = x->right;

            //rotate the nodes
            x->right = y;
            y->left = T;

            //If there was a height variable in the Node then we would 
            //recalculate height here...

            return;
        }

        //inteprets rotations
        void rotationMaker(Node* x, string word) {

            int balance = height(x->left) - height(x->right);
            //Now to perform Rotation Operations
            //CASE 1: LEFT LEFT
            if(balance > 1 && word < x->left->word) 
            {
                rotateRight(x);
                return;
            }

            //CASE 2: LEFT RIGHT
            if (balance > 1 && word > x->left->word)
            {
                rotateLeft(x->left);
                rotateRight(x);
                return;
            }

            //CASE 3: RIGHT LEFT
            if (balance < -1 && word < x->right->word)
            {
                rotateRight(x->right);
                rotateLeft(x);
                return;
            }

            //CASE 4: RIGHT RIGHT
            if (balance < -1 && word > x->right->word)
            {
                rotateLeft(x);
                return;
            }
            else return;
        }
        int height(Node* root) {
            if(root == NULL) 
                return 1;
            else return max(height(root->left), height(root->right)) + 1;
        }

        bool isBalance(Node* x) {
            int balance = height(x->left) - height(x->right);
            if(balance == 1 || 0 || -1)
                return true;
            else
                return false;
        }

        //insert functions
        void insert(string word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if(this->root != NULL){
                insert(this->root, word);
            }
            else
            {
                this->root = new Node(word);
                nodeCount += 1;
            }


        }
        void insert(Node* root, string word) {
    
            if(word < root->word)
            {
                
                if(root->left != NULL)
                    insert(root->left, word);
                else
                {
                    root->left = new Node(word);
                    nodeCount += 1;
                }  
            }
            else if(word > root->word)
            {
            
                if(root->right != NULL)
                    insert(root->right, word);
                else
                {
                    root->right = new Node(word);
                    nodeCount += 1;
                }
            }
            //word is already in the tree so we increment counter
            else  root->count += 1;

            //find the balance of the tree to know whcih sequence of 
            //rotations to perform
        //    int balance = height(root->left) - height(root->right);
            if (isBalance(root) == false)
            {
                rotationMaker(root, word);
            }
        }

        //delete function
        struct Node* deleteOne(string word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            deleteOne(root, word);
            /*else {
                cout << "\"" <<  word << "\"" << " does not exist in the tree." << endl;
            }*/
        };
        struct Node* deleteOne(Node * ptr, string word) {
            // Find the word 
            bool found = false;
            Node* predecessor=NULL; //was NULLptr -DR
            Node* current=ptr;
            if(current==NULL) {
                //do nothing
                //cout<<"Tree is empty"<<endl;
                return current; //was empty return -DR
            }
            while(current!=NULL)
            {
                if(current->word==word)
                {
                    found = true;
                    break;
                }
                else
                {
                    predecessor = current;
                    if(word > (current->word))
                        current=current->right;
                    else
                        current=current->left;
                }
            }
            if(!found)
            {
                //do nothing
                //cout<<word<<" not in Tree."<<endl;
                return current; //was empty retur -DR
            }

            //If the count of the word is greater than 1, we only need to decrement the counter
            if ( current->count > 1 ) {
                current->count -= 1;
            }
            //if there is only one instance of the word in the tree, we must delete the Node
            else {

                // CASE 1: Removing a Node with a single child
                if((current->left==NULL && current->right != NULL) || (current->left != NULL && current->right==NULL))
                {
                    // RightChild Leaf Present, No LeftChild Leaf
                    if(current->left==NULL && current->right != NULL)
                    {
                        // If predecessor's left tree equals Node ptr
                        if(predecessor->left==current)
                        {
                            // then predecessor's left tree becomes ptr's right tree
                            // and delete ptr
                            predecessor->left=current->right;
                            delete current;
                            current=NULL;
                            //cout<<word<<" has been removed from the Tree."<<endl;
                        }
                        // If predecessor's right tree equals Node ptr
                        else
                        {
                            // then predecessor's right tree becomes ptr's right tree
                            // and delete ptr
                            predecessor->right=current->right;
                            delete current;
                            current=NULL;
                            //cout<<word<<" has been removed from the Tree."<<endl;
                        }
                    }
                    else // LeftChild Leaf Present, No RightChild Leaf Present
                    {
                        if(predecessor->left==current)
                        {
                            predecessor->left=current->left;
                            delete current;
                            current=NULL;
                            //cout<<word<<" has been removed from the Tree."<<endl;
                        }
                        else
                        {
                            predecessor->right=current->left;
                            delete current;
                            current=NULL;
                            //cout<<word<<" has been removed from the Tree."<<endl;
                        }
                    }
                    return current; //was empty return -DR
                }
                // CASE 2: Removing a Leaf Node
                if(current->left==NULL && current->right==NULL)
                {
                    if(predecessor->left==current)
                        predecessor->left=NULL;
                    else
                        predecessor->right=NULL;
                    delete current;
                    //cout<<word<<" has been removed from the Tree."<<endl;
                    return current; //empty return before -DR
                }
                // CASE 3: Node has two children
                // Replace Node with smallest value in right subtree
                if(current->left != NULL && current->right != NULL)
                {
                    Node* check=current->right;
                    if((current->left==NULL)&&(current->right==NULL))
                    {
                        current=check;
                        delete check;
                        //current->right==NULL;
                        //cout<<word<<" has been removed from the Tree."<<endl;
                    }
                    else // RightChild child has children
                    {
                        // If the Node's right child has a left child
                        // Move all the way down left to locate smallest element
                        if((current->right)->left!=NULL)
                        {
                            Node* leftCurrent;
                            Node* leftCurrentPred;
                            leftCurrentPred=current->right;
                            leftCurrent=(current->right)->left;
                            while(leftCurrent->left != NULL)
                            {
                                leftCurrentPred=leftCurrent;
                                leftCurrent=leftCurrent->left;
                            }
                            current->word=leftCurrent->word;
                            delete leftCurrent;
                            //leftCurrentPred->left==NULL;
                            //cout<<word<<" has been removed from the Tree."<<endl;
                        }
                        else
                        {
                            Node* temp=current->right;
                            current->word=temp->word;
                            current->right=temp->right;
                            delete temp;
                            //cout<<word<<" has been removed from the Tree."<<endl;
                        }
                    }
                    return current; //Was originally just an empty return -DR
                }
            }
            
        };


        void lexSort() {
            ofstream outputFile;
            outputFile.open("avlSorted.txt");
            lexSort(this->root, outputFile);
            outputFile.close();
        };
        void lexSort(Node *node, ofstream &outputFile) {
            if (node != nullptr){
                
                /* first recur on left child */
                lexSort(node->left, outputFile);
                
                /* then write the data of node to an output file */
                outputFile << node->word << " ";
                //cout << node->word << "being written." << endl;
                /* now recur on right child */
                lexSort(node->right, outputFile);
                
            }
        }


        std::vector<string> rangeSearch(string begin, string end) {
            transform(begin.begin(), begin.end(), begin.begin(), ::tolower);
            transform(end.begin(), end.end(), end.begin(), ::tolower);
            //switch begin and end if end comes before begin in alphabet
            if (begin > end) {
                string temp = begin;
                begin = end;
                end = temp;
            }
            vector<string> rangeVector;
            rangeSearch(root, rangeVector, begin, end);
            return rangeVector;
        };
        void rangeSearch(Node *node, vector<string>& rangeVector, string low, string high) {
            // Base case
            if (node == NULL) return;
        
            // Special Optional case for improving efficiency
            //if (node->word == high && node->word == low)
                //cout << "adding to vector." << endl;
                //rangeVector.push_back(node->word);
        
            // If current node is in range, then include it in count and
            // recur for left and right children of it

            if (node->word <= high && node->word >= low){
                
                //cout << node->word << endl;
                //cout << "adding to vector." << endl;
                rangeSearch(node->left, rangeVector, low, high);
                rangeVector.push_back(node->word);
                //cout << node->word << endl;
                rangeSearch(node->right, rangeVector, low, high);
            }
            // If current node is smaller than low, then recur for right
            // child
            else if (node->word < low) {
                rangeSearch(node->right, rangeVector, low, high);
            }
            // Else recur for left child
            else rangeSearch(node->left, rangeVector, low, high);
        }

};

 /*
 *class implementation of an individual node in a tree
 */
class TFTNode
{
    //struct for each individual node
    struct Nodelete 
    {
        string word;
        int duplicates;

        Nodelete() : word(""), duplicates(0) {}
        Nodelete(string word) : word(word), duplicates(0) {}
    };
    struct Nodelete *words;  // An array of words
    int MAXWORDS;      // Minimum degree (defines the range for number of words)
    TFTNode **children; // An array of child pointers
    int wordsInNode;     // Current number of words
    bool leaf; // Is true when node is leaf. Otherwise false
 
public:
 
    TFTNode(int _t, bool _leaf);   // Constructor
 
    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();
 
    // A function to search a key in subtree rooted with this node.
    TFTNode *search(string word);   // returns NULL if word is not present.
 
    // A function that returns the index of the first key that is greater
    // or equal to word
    int findKey(string word);
 
    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(string word);
 
    // A utility function to split the child y of this node. i is index
    // of y in child array children[].  The Child y must be full when this
    // function is called
    void splitChild(int i, TFTNode *y);
 
    // A wrapper function to deleteOne the key word in subtree rooted with
    // this node.
    void deleteOne(string word);
 
    // A function to deleteOne the key present in idx-th position in
    // this node which is a leaf
    void removeFromLeaf(int idx);
 
    // A function to deleteOne the key present in idx-th position in
    // this node which is a non-leaf node
    void removeFromNonLeaf(int idx);
 
    // A function to get the predecessor of the key- where the key
    // is present in the idx-th position in the node
    string getPred(int idx);
 
    // A function to get the successor of the key- where the key
    // is present in the idx-th position in the node
    string getSucc(int idx);
 
    // A function to fill up the child node present in the idx-th
    // position in the children[] array if that child has less than MAXWORDS-1 words
    void fill(int idx);
 
    // A function to borrow a key from the children[idx-1]-th node and place
    // it in children[idx]th node
    void borrowFromPrev(int idx);
 
    // A function to borrow a key from the children[idx+1]-th node and place it
    // in children[idx]th node
    void borrowFromNext(int idx);
 
    // A function to merge idx-th child of the node with (idx+1)th child of
    // the node
    void merge(int idx);

    void lexSort(ofstream &outputFile);

    void rangeSearch(vector<string>& rangeVector, string low, string high);
 
    // Make TFT friend of this so that we can access private members of
    // this class in TFT functions
    friend class TFT;
};
 
class TFT
{
    TFTNode *root; // Pointer to root node
    int MAXWORDS;  // Minimum degree
public:
 
    // Constructor (Initializes tree as empty)
    TFT(int _t)
    {
        root = NULL;
        MAXWORDS = _t;
    }
 
    void traverse()
    {
        if (root != NULL) root->traverse();
    }

    void lexSort() {
        if (root != NULL) {
            ofstream outputFile;
            outputFile.open("tftSorted.txt");
            root->lexSort(outputFile);
            outputFile.close();
        }
    }
 
    // function to search a key in this tree
    TFTNode* search(string word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        return (root == NULL)? NULL : root->search(word);
    }

    //range search function
    std::vector<string> rangeSearch(string begin, string end);
 
    // The main function that inserts a new key in this B-Tree
    void insert(string word);
 
    // The main function that removes a new key in thie B-Tree
    void deleteOne(string word);
 
};
 
TFTNode::TFTNode(int t1, bool isLeaf)
{
    // Copy the given minimum degree and leaf property
    MAXWORDS = t1;
    leaf = isLeaf;
 
    // Allocate memory for maximum number of possible words
    // and child pointers
    words = new Nodelete[2*MAXWORDS-1];
    children = new TFTNode *[2*MAXWORDS];
 
    // Initialize the number of words as 0
    wordsInNode = 0;
}
 
// A utility function that returns the index of the first key that is
// greater than or equal to word
int TFTNode::findKey(string word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    int idx=0;
    while (idx<wordsInNode && words[idx].word < word)
        ++idx;
    return idx;
}
 
// A function to deleteOne the key word from the sub-tree rooted with this node
void TFTNode::deleteOne(string word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
   
    int idx = findKey(word);
 
    // The key to be removed is present in this node
    if (idx < wordsInNode && words[idx].word == word)
    {
 
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
 
        // If this node is a leaf node, then the key is not present in tree
        if (leaf)
        {
            cout << "The key "<< word <<" is does not exist in the tree\n";
            return;
        }
 
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==wordsInNode)? true : false );
 
        // If the child where the key is supposed to exist has less that MAXWORDS words,
        // we fill that child
        if (children[idx]->wordsInNode < MAXWORDS)
            fill(idx);
 
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast MAXWORDS words
        if (flag && idx > wordsInNode)
            children[idx-1]->deleteOne(word);
        else
            children[idx]->deleteOne(word);
    }
    return;
}
 
// A function to deleteOne the idx-th key from this node - which is a leaf node
void TFTNode::removeFromLeaf (int idx)
{
 
    // Move all the words after the idx-th pos one place backward
    for (int i=idx+1; i<wordsInNode; ++i)
        words[i-1].word = words[i].word;
 
    // Reduce the count of words
    wordsInNode--;
 
    return;
}
 
// A function to deleteOne the idx-th key from this node - which is a non-leaf node
void TFTNode::removeFromNonLeaf(int idx)
{
 
    string word = words[idx].word;
 
    // If the child that precedes word (children[idx]) has atleast MAXWORDS words,
    // find the predecessor 'pred' of word in the subtree rooted at
    // children[idx]. Replace word by pred. Recursively delete pred
    // in children[idx]
    if (children[idx]->wordsInNode >= MAXWORDS)
    {
        string pred = getPred(idx);
        words[idx].word = pred;
        children[idx]->deleteOne(pred);
    }
 
    // If the child children[idx] has less that MAXWORDS words, examine children[idx+1].
    // If children[idx+1] has atleast MAXWORDS words, find the successor 'succ' of word in
    // the subtree rooted at children[idx+1]
    // Replace word by succ
    // Recursively delete succ in children[idx+1]
    else if  (children[idx+1]->wordsInNode >= MAXWORDS)
    {
        string succ = getSucc(idx);
        words[idx].word = succ;
        children[idx+1]->deleteOne(succ);
    }
 
    // If both children[idx] and children[idx+1] has less that MAXWORDS words,merge word and all of children[idx+1]
    // into children[idx]
    // Now children[idx] contains 2t-1 words
    // Free children[idx+1] and recursively delete word from children[idx]
    else
    {
        merge(idx);
        children[idx]->deleteOne(word);
    }
    return;
}
 
// A function to get predecessor of words[idx]->word
string TFTNode::getPred(int idx)
{
    // Keep moving to the right most node until we reach a leaf
    TFTNode *cur=children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->wordsInNode];
 
    // Return the last key of the leaf
    return cur->words[cur->wordsInNode-1].word;
}
 
string TFTNode::getSucc(int idx)
{
 
    // Keep moving the left most node starting from children[idx+1] until we reach a leaf
    TFTNode *cur = children[idx+1];
    while (!cur->leaf)
        cur = cur->children[0];
 
    // Return the first key of the leaf
    return cur->words[0].word;
}
 
// A function to fill child children[idx] which has less than MAXWORDS-1 words
void TFTNode::fill(int idx)
{
 
    // If the previous child(children[idx-1]) has more than MAXWORDS-1 words, borrow a key
    // from that child
    if (idx!=0 && children[idx-1]->wordsInNode>=MAXWORDS)
        borrowFromPrev(idx);
 
    // If the next child(children[idx+1]) has more than MAXWORDS-1 words, borrow a key
    // from that child
    else if (idx!=wordsInNode && children[idx+1]->wordsInNode>=MAXWORDS)
        borrowFromNext(idx);
 
    // Merge children[idx] with its sibling
    // If children[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else
    {
        if (idx != wordsInNode)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}
 
// A function to borrow a key from children[idx-1] and insert it
// into children[idx]
void TFTNode::borrowFromPrev(int idx)
{
 
    TFTNode *child=children[idx];
    TFTNode *sibling=children[idx-1];
 
    // The last key from children[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in children[idx]. Thus, the  loses
    // sibling one key and child gains one key
 
    // Moving all key in children[idx] one step ahead
    for (int i=child->wordsInNode-1; i>=0; --i)
        child->words[i+1].word = child->words[i].word;
 
    // If children[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf)
    {
        for(int i=child->wordsInNode; i>=0; --i)
            child->children[i+1] = child->children[i];
    }
 
    // Setting child's first key equal to words[idx-1] from the current node
    child->words[0].word = words[idx-1].word;
 
    // Moving sibling's last child as children[idx]'s first child
    if (!leaf)
        child->children[0] = sibling->children[sibling->wordsInNode];
 
    // Moving the key from the sibling to the parent
    // This reduces the number of words in the sibling
    words[idx-1].word = sibling->words[sibling->wordsInNode-1].word;
 
    child->wordsInNode += 1;
    sibling->wordsInNode -= 1;
 
    return;
}
 
// A function to borrow a key from the children[idx+1] and place
// it in children[idx]
void TFTNode::borrowFromNext(int idx)
{
 
    TFTNode *child=children[idx];
    TFTNode *sibling=children[idx+1];
 
    // words[idx] is inserted as the last key in children[idx]
    child->words[(child->wordsInNode)].word = words[idx].word;
 
    // Sibling's first child is inserted as the last child
    // into children[idx]
    if (!(child->leaf))
        child->children[(child->wordsInNode)+1] = sibling->children[0];
 
    //The first key from sibling is inserted into words[idx].word
    words[idx].word = sibling->words[0].word;
 
    // Moving all words in sibling one step behind
    for (int i=1; i<sibling->wordsInNode; ++i)
        sibling->words[i-1].word = sibling->words[i].word;
 
    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->wordsInNode; ++i)
            sibling->children[i-1] = sibling->children[i];
    }
 
    // Increasing and decreasing the key count of children[idx] and children[idx+1]
    // respectively
    child->wordsInNode += 1;
    sibling->wordsInNode -= 1;
 
    return;
}
 
// A function to merge children[idx] with children[idx+1]
// children[idx+1] is freed after merging
void TFTNode::merge(int idx)
{
    TFTNode *child = children[idx];
    TFTNode *sibling = children[idx+1];
 
    // Pulling a key from the current node and inserting it into (MAXWORDS-1)th
    // position of children[idx]
    child->words[MAXWORDS-1].word = words[idx].word;
 
    // Copying the words from children[idx+1] to children[idx] at the end
    for (int i=0; i<sibling->wordsInNode; ++i)
        child->words[i+MAXWORDS].word = sibling->words[i].word;
 
    // Copying the child pointers from children[idx+1] to children[idx]
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->wordsInNode; ++i)
            child->children[i+MAXWORDS] = sibling->children[i];
    }
 
    // Moving all words after idx in the current node one step before -
    // to fill the gap created by moving words[idx].word to children[idx]
    for (int i=idx+1; i<wordsInNode; ++i)
        words[i-1].word = words[i].word;
 
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=idx+2; i<=wordsInNode; ++i)
        children[i-1] = children[i];
 
    // Updating the key count of child and the current node
    child->wordsInNode += sibling->wordsInNode+1;
    wordsInNode--;
 
    // Freeing the memory occupied by sibling
    delete(sibling);
    return;
}
 
// The main function that inserts a new key in this B-Tree
void TFT::insert(string word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);


    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new TFTNode(MAXWORDS, true);
        //initialize nodelete with a word and set it equal to the root's
        //first nodelete
        root->words[0].word = word;  // Insert key
        root->words[0].duplicates = 1;

        root->wordsInNode = 1;  // Update number of words in root
    }
    else {
        //search if the word exists in the tree
        //If it does, just add to the duplicate value of that Nodelete
        TFTNode *ptr = root->search(word);
        if(!ptr) // If tree is not empty
        {
            // If root is full, then tree grows in height
            if (root->wordsInNode == 2*MAXWORDS-1)
            {
                // Allocate memory for new root
                TFTNode *s = new TFTNode(MAXWORDS, false);
    
                // Make old root as child of new root
                s->children[0] = root;
    
                // Split the old root and move 1 key to the new root
                s->splitChild(0, root);
    
                // New root has two children now.  Decide which of the
                // two children is going to have new key
                int i = 0;
                if (s->words[0].word < word)
                    i++;
                s->children[i]->insertNonFull(word);

    
                // Change root
                root = s;
            }
            else  // If root is not full, call insertNonFull for root
                root->insertNonFull(word);
        }
        else {

            for(int i = 0; i < ptr->wordsInNode; i++) {
                if(ptr->words[i].word == word) 
                    ptr->words[i].duplicates += 1;
            }
            
        }
    }
}
 
// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void TFTNode::insertNonFull(string word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    // Initialize index as index of rightmost element
    int i = wordsInNode-1;
 
    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater words to one place ahead
        while (i >= 0 && words[i].word > word)
        {
            words[i+1].word = words[i].word;
            i--;
        }
 
        // Insert the new key at found location
        words[i+1].word = word;
        wordsInNode = wordsInNode+1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && words[i].word > word)
            i--;
 
        // See if the found child is full
        if (children[i+1]->wordsInNode == 2*MAXWORDS-1)
        {
            // If the child is full, then split it
            splitChild(i+1, children[i+1]);
 
            // After split, the middle key of children[i] goes up and
            // children[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (words[i+1].word < word)
                i++;
        }
        children[i+1]->insertNonFull(word);
    }
}
 
// A utility function to split the child y of this node
// Note that y must be full when this function is called
void TFTNode::splitChild(int i, TFTNode *y)
{
    // Create a new node which is going to store (MAXWORDS-1) words
    // of y
    TFTNode *z = new TFTNode(y->MAXWORDS, y->leaf);
    z->wordsInNode = MAXWORDS - 1;
 
    // Copy the last (MAXWORDS-1) words of y to z
    for (int j = 0; j < MAXWORDS-1; j++)
        z->words[j].word = y->words[j+MAXWORDS].word;
 
    // Copy the last MAXWORDS children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < MAXWORDS; j++)
            z->children[j] = y->children[j+MAXWORDS];
    }
 
    // Reduce the number of words in y
    y->wordsInNode = MAXWORDS - 1;
 
    // Since this node is going to have a new child,
    // create space of new child
    for (int j = wordsInNode; j >= i+1; j--)
        children[j+1] = children[j];
 
    // Link the new child to this node
    children[i+1] = z;
 
    // A key of y will move to this node. Find location of
    // new key and move all greater words one space ahead
    for (int j = wordsInNode-1; j >= i; j--)
        words[j+1].word = words[j].word;
 
    // Copy the middle key of y to this node
    words[i].word = y->words[MAXWORDS-1].word;
 
    // Increment count of words in this node
    wordsInNode = wordsInNode + 1;
}
 
// Function to traverse all nodes in a subtree rooted with this node
void TFTNode::traverse()
{
    // There are wordsInNode words and wordsInNode+1 children, travers through wordsInNode words
    // and first wordsInNode children
    int i;
    for (i = 0; i < wordsInNode; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child children[i].
        if (leaf == false)
            children[i]->traverse();
        cout << " " << words[i].word;
    }
 
    // Print the subtree rooted with last child
    if (leaf == false)
        children[i]->traverse();
}
 
// Function to search key word in subtree rooted with this node
TFTNode *TFTNode::search(string word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    // Find the first key greater than or equal to word
    int i = 0;
    while (i < wordsInNode && word > words[i].word)
        i++;
 
    // If the found key is equal to word, return this node
    if (words[i].word == word)
        return this;
 
    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;
 
    // Go to the appropriate child
    return children[i]->search(word);
}
 
void TFT::deleteOne(string word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }
 
     
    //find if the word exists in the tree.
    //If it does, take one away from the duplicate
    //If duplicate reaches 0, delete the Nodelete from the tree
    TFTNode* ptr = root->search(word);
    int idx;
    for(int i = 0; i < ptr->wordsInNode; i++) {
        if(ptr->words[i].word == word)
            idx = i;
    }
    //if there is only one instance of the word, delete Nodelete
    cout << "number : " << ptr->words[idx].duplicates << endl;
    if(ptr->words[idx].duplicates == 1) {

        // Call the deleteOne function for root
        root->deleteOne(word);
    
        // If the root node has 0 words, make its first child as the new root
        //  if it has a child, otherwise set root as NULL
        if (root->wordsInNode==0)
        {
            TFTNode *tmp = root;
            if (root->leaf)
                root = NULL;
            else
                root = root->children[0];
    
            // Free the old root
            delete tmp;
        }
    }
    else {
        ptr->words[idx].duplicates -= 1;
    }
    return;
}

//A function to traverse throughout the tree and write every word in the
//tree to an output file lexocographically!!!
void TFTNode::lexSort(ofstream &outputFile)
{
    // There are wordsInNode words and wordsInNode+1 children, travers through wordsInNode words
    // and first wordsInNode children
    int i;
    for (i = 0; i < wordsInNode; i++)
    {
        // If this is not leaf, then before printing key[i],
        // lexSort the subtree rooted with child children[i].
        if (leaf == false)
            children[i]->lexSort(outputFile);
        outputFile << words[i].word << " ";
    }

    // Print the subtree rooted with last child
    if (leaf == false)
        children[i]->lexSort(outputFile);
}

std::vector<string> TFT::rangeSearch(string begin, string end) {
    transform(begin.begin(), begin.end(), begin.begin(), ::tolower);
    transform(end.begin(), end.end(), end.begin(), ::tolower);
    //switch begin and end if end comes before begin in alphabet
    if (begin > end) {
        string temp = begin;
        begin = end;
        end = temp;
    }
    vector<string> rangeVector;
    root->rangeSearch(rangeVector, begin, end);
    return rangeVector;
}

void TFTNode::rangeSearch(vector<string>& rangeVector, string low, string high) {

    // There are wordsInNode words and wordsInNode+1 children, travers through wordsInNode words
    // and first wordsInNode children
    int i;
    for (i = 0; i < wordsInNode; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child children[i].
        if (leaf == false)
            children[i]->rangeSearch(rangeVector, low, high);

        // If current node is in range, then include it in count and
        // recur for left and right children of it
        if (words[i].word <= high && words[i].word >= low)
            rangeVector.push_back(words[i].word);
    }
 
    // Print the subtree rooted with last child
    if(leaf == false)
        children[i]->rangeSearch(rangeVector, low, high);
};

//Handles directories
void parseFileInsert(AVL& avl, TFT& tft, string fullPath) {
    ifstream infile;
    infile.open(fullPath); // Open it up!
    std::string line;
    char c;
    string word = "";
    //int jerry = 0;
    while (getline(infile, line))
    {
        // Iterate through the string one letter at a time.
        for (int i = 0; i < line.length(); i++) {

            c = line.at(i); // Get a char from string
            tolower(c);        
            // if it's NOT within these bounds, then it's not a character
            if (! ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ) ) {

                //if word is NOT an empty string, insert word into bst
                if ( word != "" ) {
                    avl.insert(word);
                    tft.insert(word);
                    //jerry += 1;
                    //cout << jerry << endl;
                    //reset word string
                    word = "";
                }
            }
            else {
                word += string(1, c);
            }
        }
    }
    
};
 
//This is a function used in main to traverse the directories and feed
//path names into parseFileInsert for words to be inserted into data structures
void recurseDir(AVL& avl,TFT& tft, const string path, vector<string> files,const bool showHiddenDirs = false){
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir(path.c_str());
    int count = 0;
    if (dpdf != NULL){
        while ((epdf = readdir(dpdf)) != NULL){
            if(showHiddenDirs ? (epdf->d_type==DT_DIR && string(epdf->d_name) != ".." && string(epdf->d_name) != "." ) : (epdf->d_type==DT_DIR && strstr(epdf->d_name,"..") == NULL && strstr(epdf->d_name,".") == NULL ) ){
                recurseDir(avl, tft, path+epdf->d_name+"/",files, showHiddenDirs);
            }
            if(epdf->d_type==DT_REG){
                
                parseFileInsert(avl, tft, path+epdf->d_name);
            }
        }
    }
    closedir(dpdf);
}

// Driver program to test above functions
int main()
{
    //Start of Project
	//create a new text file
	
    //create an AVL tree
	AVL avl;
    //create a 2-5 Tree that holds a max of 4 words in each node
	TFT tft(4);

    //build the data structures from the data base given
    string path = "test/";
	vector<string> files;
	recurseDir(avl, tft, path, files, false);

    char input = 0;
	while (input != 'q')
	{
		cout << "Enter a number to preform functionality" << endl;
		cout << "1 = search" << endl
			<< "2 = insert" << endl
			<< "3 = delete" << endl
			<< "4 = sort"   << endl
			<< "5 = range search" << endl
			<< "q = quit program" << endl; 
		cin >> input;
		
	
        switch(input)
        {
            case '1' :
                {
                    cout << "You selected to search" << endl
                        << "Please type a word to search" << endl;
                    string Input;
                    cin >> Input;

                    //AVL search function
                    //timing fucntions to clock speed of functions
                    clock_t time_req_AVL;
                    time_req_AVL = clock();
                    bool isInAVL = avl.search(Input);
                    time_req_AVL = clock() - time_req_AVL;

                    //TFT search function
                    clock_t time_req_TFT;
                    time_req_TFT = clock();
                    bool isInTFT = tft.search(Input);
                    time_req_TFT = clock() - time_req_TFT;

                    //print truth value of word's existence based on searches of both data bases
                    if(isInAVL && isInTFT) cout << "true" << endl;
                    else cout << "false" << endl;

                    //print timing values of functions
                    cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
                    cout << "2-5: " << (float)time_req_TFT/CLOCKS_PER_SEC << "s" << endl;
                    break;
                }

            case '2' :
                {
                    cout << "You selected to insert" << endl
                        << "Please type a word to insert" << endl;
                    string Input;
                    cin >> Input;

                    //AVL insert function
                    clock_t time_req_AVL;
                    time_req_AVL = clock();
                    avl.insert(Input);
                    time_req_AVL = clock() - time_req_AVL;

                    //TFT insert function
                    clock_t time_req_TFT;
                    time_req_TFT = clock();
                    tft.insert(Input);
                    time_req_TFT = clock() - time_req_TFT;

                    //print timing values of functions
                    cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
                    cout << "2-5: " << (float)time_req_TFT/CLOCKS_PER_SEC << "s" << endl;
                    break;
                }

            case '3' :
                {
                    cout << "You selected to delete" << endl
                        << "Please type a word to delete" << endl;
                    string Input;
                    cin >> Input;

                    //AVL deleteOne function
                    clock_t time_req_AVL;
                    time_req_AVL = clock();
                    avl.deleteOne(Input);
                    time_req_AVL = clock() - time_req_AVL;

                    //TFT deleteOne function
                    clock_t time_req_TFT;
                    time_req_TFT = clock();
                    tft.deleteOne(Input);
                    time_req_TFT = clock() - time_req_TFT;

                    

                    //print timing values of functions
                    cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
                    cout << "2-5: " << (float)time_req_TFT/CLOCKS_PER_SEC << "s" << endl;
                    break;
                }

            case '4' :
                {
                    
                    cout << "You selected to sort" << endl;
        
                    //AVL deleteOne function
                    clock_t time_req_AVL;
                    time_req_AVL = clock();
                    avl.lexSort();
                    time_req_AVL = clock() - time_req_AVL;


                    //TFT deleteOne function
                    clock_t time_req_TFT;
                    time_req_TFT = clock();
                    tft.lexSort();
                    time_req_TFT = clock() - time_req_TFT;

                    //print values of timing functions
                    cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
                    cout << "2-5: " << (float)time_req_TFT/CLOCKS_PER_SEC << "s" << endl;
                    break;
                    
                }
            
            case '5' :
                {
                    
                    cout << "You selected to range search" << endl
                        << "Please type your first word to Range search" << endl;
                    
                    string Input1;
                    cin >> Input1;
                    cout << "Please type your second word to Range search" << endl;
                    string Input2;
                    cin >> Input2;
                    
                    //AVL rangeSearch function
                    clock_t time_req_AVL;
                    time_req_AVL = clock();
                    vector<string> avlvec = avl.rangeSearch(Input1, Input2);
                    time_req_AVL = clock() - time_req_AVL;
                    //print out AVL contents
                    for (std::vector<string>::const_iterator i = avlvec.begin(); i != avlvec.end(); ++i)
                        std::cout << *i << ' ';
                    cout << endl;

                    //TFT rangeSearch function
                    clock_t time_req_TFT;
                    time_req_TFT = clock();
                    vector<string> tftvec = tft.rangeSearch(Input1, Input2);
                    time_req_TFT = clock() - time_req_TFT;
                    //print out TFT contents
                    for (std::vector<string>::const_iterator i = tftvec.begin(); i != tftvec.end(); ++i)
                        std::cout << *i << ' ';
                    cout << endl;

                    //print values of timing functions
                    cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
                    cout << "2-5: " << (float)time_req_TFT/CLOCKS_PER_SEC << "s" << endl;
                    break;
                    
                }
            case 'q' : {
                cout << "Program has finished." << endl;
                break;}
            default: {
                cout << "not a valid input.\n\n";
                break;
            }
        }

    
	}

 
    return 0;
}