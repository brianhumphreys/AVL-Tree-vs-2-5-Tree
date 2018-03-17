#include "AVL.h"
#include "TFT.h"
#include "TFTNode.h"

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
#include <boost>
 
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
                cout << path+epdf->d_name << endl;
                parseFileInsert(avl, tft, path+epdf->d_name);
            }
        }
    }
    closedir(dpdf);
}


int main()
{
    //Start of Project
	//create a new text file
	
    //create an AVL tree
	AVL avl;
    //create a 2-5 Tree that holds a max of 4 words in each node
	TFT tft(4);

    boost::filesystem::path p("C:\\folder\\foo.txt");
    boost::filesystem::path dir = p.parent_path();

    cout << dir<< endl << endl;


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

                    //create an output file to store sorted words
                    ofstream outputFile;
                    outputFile.open("output.txt");

                    //AVL deleteOne function
                    clock_t time_req_AVL;
                    time_req_AVL = clock();
                    avl.lexSort(outputFile);
                    time_req_AVL = clock() - time_req_AVL;

                    outputFile << endl;

                    //TFT deleteOne function
                    clock_t time_req_TFT;
                    time_req_TFT = clock();
                    tft.lexSort(outputFile);
                    time_req_TFT = clock() - time_req_TFT;

                    //close output file out show file path
                    outputFile.close();

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

                case 'q' : 
                {
                    cout << "Program has finished." << endl;
                 break;
                }

                default: 
                {
                    cout << "not a valid input.\n\n";
                    break;
                }
            }
        }
    return 0;
}
