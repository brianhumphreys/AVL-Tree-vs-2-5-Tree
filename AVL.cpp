#include "AVL.h"

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

AVL::AVL(void) 
{
    root = NULL;
    nodeCount = 0;
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

void AVL::printTree() 
{
    printTree(root);
}
        
void AVL::printTree(Node * root) 
{
    if(root != NULL) 
    {
        printTree(root->left);
        cout << " " << root->word;
        printTree(root->right);
    }
}

        //search functions
bool AVL::search(string word) 
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return searchHelper(root, word);
}

bool AVL::searchHelper(struct Node* root, string word) 
{
    if(root == NULL) 
        return false;
    else if (word < root->word)
        return searchHelper(root->left, word);
    else if (word > root->word)
        return searchHelper(root->right, word);
    else return true;
}

void AVL::rotateLeft(Node* y) 
{
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

void AVL::rotateRight(Node* y) 
{
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

void AVL::rotationMaker(Node* x, string word) 
{
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

int AVL::height(Node* root) 
{
    if(root == NULL) 
        return 1;
    else return max(height(root->left), height(root->right)) + 1;
}

bool AVL::isBalance(Node* x) 
{
    int balance = height(x->left) - height(x->right);
    if(balance == 1 || 0 || -1)
        return true;
    else
        return false;
}

void AVL::insert(string word) 
{
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

void AVL::insert(Node* root, string word) 
{
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
    //int balance = height(root->left) - height(root->right);
    if (isBalance(root) == false)
    {
        rotationMaker(root, word);
    }
}

//delete function
struct AVL::Node* AVL::deleteOne(string word) 
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    deleteOne(root, word);
};

 struct AVL::Node* AVL::deleteOne(Node * ptr, string word) 
 {
    // Find the word 
    bool found = false;
    Node* predecessor=NULL; //was NULLptr -DR
    Node* current=ptr;
    if(current==NULL)
    {
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
    if (current->count > 1) 
    {
        current->count -= 1;
    }
    //if there is only one instance of the word in the tree, we must delete the Node
    else 
    {
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

 void AVL::lexSort() 
 {
    ofstream outputFile;
    outputFile.open("avlSorted.txt");
    lexSort(this->root, outputFile);
    outputFile.close();
};

void AVL::lexSort(Node *node, ofstream &outputFile) 
{
    if (node != nullptr)
    {
        /* first recur on left child */
        lexSort(node->left, outputFile);

        /* then write the data of node to an output file */
        outputFile << node->word << " ";
        //cout << node->word << "being written." << endl;
        /* now recur on right child */
        lexSort(node->right, outputFile);   
    }
}

std::vector<string> AVL::rangeSearch(string begin, string end) 
{
    transform(begin.begin(), begin.end(), begin.begin(), ::tolower);
    transform(end.begin(), end.end(), end.begin(), ::tolower);
    //switch begin and end if end comes before begin in alphabet
    if (begin > end) 
    {
        string temp = begin;
        begin = end;
        end = temp;
    }
    vector<string> rangeVector;
    rangeSearch(root, rangeVector, begin, end);
    return rangeVector;
};

 void AVL::rangeSearch(Node *node, vector<string>& rangeVector, string low, string high) 
 {
    // Base case
    if (node == NULL) 
        return;            
        // Special Optional case for improving efficiency
        //if (node->word == high && node->word == low)
        //cout << "adding to vector." << endl;
        //rangeVector.push_back(node->word);
        
        // If current node is in range, then include it in count and
        // recur for left and right children of it
        if (node->word <= high && node->word >= low)
        { 
            //cout << node->word << endl;
            //cout << "adding to vector." << endl;
            rangeSearch(node->left, rangeVector, low, high);
            rangeVector.push_back(node->word);
            //cout << node->word << endl;
            rangeSearch(node->right, rangeVector, low, high);
        }
        // If current node is smaller than low, then recur for right
        // child
        else if (node->word < low) 
        {
            rangeSearch(node->right, rangeVector, low, high);
        }
            // Else recur for left child
        else rangeSearch(node->left, rangeVector, low, high);
}

