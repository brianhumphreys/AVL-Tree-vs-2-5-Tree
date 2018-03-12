#include "TFT.h"

using namespace std;

TFT::TFT(int _t)
{
    root = NULL;
    MAXWORDS = _t;
}
 
 void TFT::traverse()
{
    if (root != NULL) root->traverse();
}

void TFT::lexSort() 
{
    if (root != NULL) 
    {
        ofstream outputFile;
        outputFile.open("tftSorted.txt");
        root->lexSort(outputFile);
        outputFile.close();
    }
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

//Handles directories
void TFT::parseFileInsert(AVL& avl, TFT& tft, string fullPath) {
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
