#include "TFTNode.h"
using namespace std;

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


