#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
                cout << root->word << endl;
                printTree(root->right);
            }
        }

        //search functions
	    void search(string word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            searchHelper(root, word);
        }
        void searchHelper(struct Node* root, string word) {
            if(root == NULL) 
                cout << "false" << endl;
            else if (word < root->word)
                searchHelper(root->left, word);
            else if (word > root->word)
                searchHelper(root->right, word);
            else cout << "true" << endl;
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
            cout << nodeCount << endl;
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

        //Handles directories
        void parseFileInsert(string fullPath) {
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
                            insert(word);
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
            /*bool foundBegin = false;
            bool foundEnd = false;*/
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
                cout << node->word << endl;
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
    int *words;  // An array of words
    int t;      // Minimum degree (defines the range for number of words)
    TFTNode **C; // An array of child pointers
    int n;     // Current number of words
    bool leaf; // Is true when node is leaf. Otherwise false
 
public:
 
    TFTNode(int _t, bool _leaf);   // Constructor
 
    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();
 
    // A function to search a key in subtree rooted with this node.
    TFTNode *search(int k);   // returns NULL if k is not present.
 
    // A function that returns the index of the first key that is greater
    // or equal to k
    int findKey(int k);
 
    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k);
 
    // A utility function to split the child y of this node. i is index
    // of y in child array C[].  The Child y must be full when this
    // function is called
    void splitChild(int i, TFTNode *y);
 
    // A wrapper function to remove the key k in subtree rooted with
    // this node.
    void remove(int k);
 
    // A function to remove the key present in idx-th position in
    // this node which is a leaf
    void removeFromLeaf(int idx);
 
    // A function to remove the key present in idx-th position in
    // this node which is a non-leaf node
    void removeFromNonLeaf(int idx);
 
    // A function to get the predecessor of the key- where the key
    // is present in the idx-th position in the node
    int getPred(int idx);
 
    // A function to get the successor of the key- where the key
    // is present in the idx-th position in the node
    int getSucc(int idx);
 
    // A function to fill up the child node present in the idx-th
    // position in the C[] array if that child has less than t-1 words
    void fill(int idx);
 
    // A function to borrow a key from the C[idx-1]-th node and place
    // it in C[idx]th node
    void borrowFromPrev(int idx);
 
    // A function to borrow a key from the C[idx+1]-th node and place it
    // in C[idx]th node
    void borrowFromNext(int idx);
 
    // A function to merge idx-th child of the node with (idx+1)th child of
    // the node
    void merge(int idx);
 
    // Make BTree friend of this so that we can access private members of
    // this class in BTree functions
    friend class BTree;
};
 
class BTree
{
    TFTNode *root; // Pointer to root node
    int t;  // Minimum degree
public:
 
    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }
 
    void traverse()
    {
        if (root != NULL) root->traverse();
    }
 
    // function to search a key in this tree
    TFTNode* search(int k)
    {
        return (root == NULL)? NULL : root->search(k);
    }
 
    // The main function that inserts a new key in this B-Tree
    void insert(int k);
 
    // The main function that removes a new key in thie B-Tree
    void remove(int k);
 
};
 
TFTNode::TFTNode(int t1, bool leaf1)
{
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;
 
    // Allocate memory for maximum number of possible words
    // and child pointers
    words = new int[2*t-1];
    C = new TFTNode *[2*t];
 
    // Initialize the number of words as 0
    n = 0;
}
 
// A utility function that returns the index of the first key that is
// greater than or equal to k
int TFTNode::findKey(int k)
{
    int idx=0;
    while (idx<n && words[idx] < k)
        ++idx;
    return idx;
}
 
// A function to remove the key k from the sub-tree rooted with this node
void TFTNode::remove(int k)
{
    int idx = findKey(k);
 
    // The key to be removed is present in this node
    if (idx < n && words[idx] == k)
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
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
 
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==n)? true : false );
 
        // If the child where the key is supposed to exist has less that t words,
        // we fill that child
        if (C[idx]->n < t)
            fill(idx);
 
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t words
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}
 
// A function to remove the idx-th key from this node - which is a leaf node
void TFTNode::removeFromLeaf (int idx)
{
 
    // Move all the words after the idx-th pos one place backward
    for (int i=idx+1; i<n; ++i)
        words[i-1] = words[i];
 
    // Reduce the count of words
    n--;
 
    return;
}
 
// A function to remove the idx-th key from this node - which is a non-leaf node
void TFTNode::removeFromNonLeaf(int idx)
{
 
    int k = words[idx];
 
    // If the child that precedes k (C[idx]) has atleast t words,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
        words[idx] = pred;
        C[idx]->remove(pred);
    }
 
    // If the child C[idx] has less that t words, examine C[idx+1].
    // If C[idx+1] has atleast t words, find the successor 'succ' of k in
    // the subtree rooted at C[idx+1]
    // Replace k by succ
    // Recursively delete succ in C[idx+1]
    else if  (C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
        words[idx] = succ;
        C[idx+1]->remove(succ);
    }
 
    // If both C[idx] and C[idx+1] has less that t words,merge k and all of C[idx+1]
    // into C[idx]
    // Now C[idx] contains 2t-1 words
    // Free C[idx+1] and recursively delete k from C[idx]
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}
 
// A function to get predecessor of words[idx]
int TFTNode::getPred(int idx)
{
    // Keep moving to the right most node until we reach a leaf
    TFTNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
 
    // Return the last key of the leaf
    return cur->words[cur->n-1];
}
 
int TFTNode::getSucc(int idx)
{
 
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    TFTNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];
 
    // Return the first key of the leaf
    return cur->words[0];
}
 
// A function to fill child C[idx] which has less than t-1 words
void TFTNode::fill(int idx)
{
 
    // If the previous child(C[idx-1]) has more than t-1 words, borrow a key
    // from that child
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);
 
    // If the next child(C[idx+1]) has more than t-1 words, borrow a key
    // from that child
    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);
 
    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}
 
// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void TFTNode::borrowFromPrev(int idx)
{
 
    TFTNode *child=C[idx];
    TFTNode *sibling=C[idx-1];
 
    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key
 
    // Moving all key in C[idx] one step ahead
    for (int i=child->n-1; i>=0; --i)
        child->words[i+1] = child->words[i];
 
    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }
 
    // Setting child's first key equal to words[idx-1] from the current node
    child->words[0] = words[idx-1];
 
    // Moving sibling's last child as C[idx]'s first child
    if (!leaf)
        child->C[0] = sibling->C[sibling->n];
 
    // Moving the key from the sibling to the parent
    // This reduces the number of words in the sibling
    words[idx-1] = sibling->words[sibling->n-1];
 
    child->n += 1;
    sibling->n -= 1;
 
    return;
}
 
// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void TFTNode::borrowFromNext(int idx)
{
 
    TFTNode *child=C[idx];
    TFTNode *sibling=C[idx+1];
 
    // words[idx] is inserted as the last key in C[idx]
    child->words[(child->n)] = words[idx];
 
    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->leaf))
        child->C[(child->n)+1] = sibling->C[0];
 
    //The first key from sibling is inserted into words[idx]
    words[idx] = sibling->words[0];
 
    // Moving all words in sibling one step behind
    for (int i=1; i<sibling->n; ++i)
        sibling->words[i-1] = sibling->words[i];
 
    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }
 
    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;
 
    return;
}
 
// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void TFTNode::merge(int idx)
{
    TFTNode *child = C[idx];
    TFTNode *sibling = C[idx+1];
 
    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->words[t-1] = words[idx];
 
    // Copying the words from C[idx+1] to C[idx] at the end
    for (int i=0; i<sibling->n; ++i)
        child->words[i+t] = sibling->words[i];
 
    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t] = sibling->C[i];
    }
 
    // Moving all words after idx in the current node one step before -
    // to fill the gap created by moving words[idx] to C[idx]
    for (int i=idx+1; i<n; ++i)
        words[i-1] = words[i];
 
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=idx+2; i<=n; ++i)
        C[i-1] = C[i];
 
    // Updating the key count of child and the current node
    child->n += sibling->n+1;
    n--;
 
    // Freeing the memory occupied by sibling
    delete(sibling);
    return;
}
 
// The main function that inserts a new key in this B-Tree
void BTree::insert(int k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new TFTNode(t, true);
        root->words[0] = k;  // Insert key
        root->n = 1;  // Update number of words in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2*t-1)
        {
            // Allocate memory for new root
            TFTNode *s = new TFTNode(t, false);
 
            // Make old root as child of new root
            s->C[0] = root;
 
            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);
 
            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->words[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
 
            // Change root
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}
 
// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void TFTNode::insertNonFull(int k)
{
    // Initialize index as index of rightmost element
    int i = n-1;
 
    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater words to one place ahead
        while (i >= 0 && words[i] > k)
        {
            words[i+1] = words[i];
            i--;
        }
 
        // Insert the new key at found location
        words[i+1] = k;
        n = n+1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && words[i] > k)
            i--;
 
        // See if the found child is full
        if (C[i+1]->n == 2*t-1)
        {
            // If the child is full, then split it
            splitChild(i+1, C[i+1]);
 
            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (words[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}
 
// A utility function to split the child y of this node
// Note that y must be full when this function is called
void TFTNode::splitChild(int i, TFTNode *y)
{
    // Create a new node which is going to store (t-1) words
    // of y
    TFTNode *z = new TFTNode(y->t, y->leaf);
    z->n = t - 1;
 
    // Copy the last (t-1) words of y to z
    for (int j = 0; j < t-1; j++)
        z->words[j] = y->words[j+t];
 
    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
 
    // Reduce the number of words in y
    y->n = t - 1;
 
    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
 
    // Link the new child to this node
    C[i+1] = z;
 
    // A key of y will move to this node. Find location of
    // new key and move all greater words one space ahead
    for (int j = n-1; j >= i; j--)
        words[j+1] = words[j];
 
    // Copy the middle key of y to this node
    words[i] = y->words[t-1];
 
    // Increment count of words in this node
    n = n + 1;
}
 
// Function to traverse all nodes in a subtree rooted with this node
void TFTNode::traverse()
{
    // There are n words and n+1 children, travers through n words
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse();
        cout << " " << words[i];
    }
 
    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}
 
// Function to search key k in subtree rooted with this node
TFTNode *TFTNode::search(int k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > words[i])
        i++;
 
    // If the found key is equal to k, return this node
    if (words[i] == k)
        return this;
 
    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;
 
    // Go to the appropriate child
    return C[i]->search(k);
}
 
void BTree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }
 
    // Call the remove function for root
    root->remove(k);
 
    // If the root node has 0 words, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->n==0)
    {
        TFTNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];
 
        // Free the old root
        delete tmp;
    }
    return;
}
 
// Driver program to test above functions
int main()
{
    BTree t(3); // A B-Tree with minium degree 3
 
    t.insert(1);
    t.insert(3);
    t.insert(7);
    t.insert(10);
    t.insert(11);
    t.insert(13);
    t.insert(14);
    t.insert(15);
    t.insert(18);
    t.insert(16);
    t.insert(19);
    t.insert(24);
    t.insert(25);
    t.insert(26);
    t.insert(21);
    t.insert(4);
    t.insert(5);
    t.insert(20);
    t.insert(22);
    t.insert(2);
    t.insert(17);
    t.insert(12);
    t.insert(6);
 
    cout << "Traversal of tree constructed is\n";
    t.traverse();
    cout << endl;
 
    t.remove(6);
    cout << "Traversal of tree after removing 6\n";
    t.traverse();
    cout << endl;
 
    t.remove(13);
    cout << "Traversal of tree after removing 13\n";
    t.traverse();
    cout << endl;
 
    t.remove(7);
    cout << "Traversal of tree after removing 7\n";
    t.traverse();
    cout << endl;
 
    t.remove(4);
    cout << "Traversal of tree after removing 4\n";
    t.traverse();
    cout << endl;
 
    t.remove(2);
    cout << "Traversal of tree after removing 2\n";
    t.traverse();
    cout << endl;
 
    t.remove(16);
    cout << "Traversal of tree after removing 16\n";
    t.traverse();
    cout << endl;
 
    return 0;
}