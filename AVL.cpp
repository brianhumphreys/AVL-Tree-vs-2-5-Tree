#include <string>
#include "AVL.h"

using namespace std;



AVL::AVL(void) {
    root->word = "";
    root->count = 0;
    root->right = NULL;
    root->left = NULL;
}

AVL::~AVL()
{
    destroyRecursive(root);
}

void AVL::destroyRecursive(Node* node)
{
    if (node)
    {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

struct AVL::Node* AVL::search(string word) {
    return searchHelper(root, word);
}

struct AVL::Node * AVL::searchHelper(struct Node* root, string word) {
        if(root == NULL) 
			return root;
		else if (word < root->word)
			return searchHelper(root->left, word);
		else if (word > root->word)
			return searchHelper(root->right, word);
		else return root;
}


int AVL::height(Node* root) {
    if(root == NULL) 
        return 1;
    else return max(height(root->left), height(root->right)) + 1;
}

struct AVL::Node* AVL::rotateLeft(Node* y) {

    //label the nodes to be rotated
    Node* x = y->right;
    Node* T = x->left;

    //rotate the nodes
    x->left = y;
    y->right = T;

    //If there was a height variable in the Node then we would 
    //recalculate height here...

    return x;

}

struct AVL::Node* AVL::rotateRight(Node* y) {
    //label the nodes to be rotated
    Node* x = y->left;
    Node* T = x->right;

    //rotate the nodes
    x->right = y;
    y->left = T;

    //If there was a height variable in the Node then we would 
    //recalculate height here...

    return x;
}

struct AVL::Node* AVL::insert(string word) {
    return insert(root, word);

}

struct AVL::Node* AVL::insert(Node* root, string word) {

    if(word < root->word)
    {
        nodeCount += 1;
        if(root->leftChild != NULL)
            insert(word, root->leftChild);
        else
        {
            root->leftChild = new node;
            root->leftChild->word = word;
            root->leftChild->count = 1;
            root->leftChild->leftChild = NULL;    //Sets the leftChild child of the child node to null
            root->leftChild->rightChild = NULL;   //Sets the rightChild child of the child node to null
        }  
    }
    else if(word > root->word)
    {
        nodeCount += 1;
        if(root->rightChild != NULL)
            insert(word, root->rightChild);
        else
        {
            root->rightChild = new node;
            root->rightChild->word = word;
            root->rightChild->count = 1;
            root->rightChild->leftChild = NULL;  //Sets the leftChild child of the child node to null
            root->rightChild->rightChild = NULL; //Sets the rightChild child of the child node to null
        }
    }
    //word is already in the tree so we increment counter
    else  root->count += 1;


    //find the balance of the tree to know whcih sequence of 
    //rotations to perform
    int balance = height(root->left) - height(root->right);

    //Now to perform Rotation Operations
    //CASE 1: LEFT LEFT
    if(balance > 1 && word < root->left->word) 
        return rotateRight(root);


}
