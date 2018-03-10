#include "AVL.h"
#include "TFT.h"

#include <functional>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <ctime>

using namespace std;


void recurseDir(AVL& avl, const string path, vector<string> files,const bool showHiddenDirs = false){
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir(path.c_str());
    int count = 0;
    if (dpdf != NULL){
        while ((epdf = readdir(dpdf)) != NULL){
            if(showHiddenDirs ? (epdf->d_type==DT_DIR && string(epdf->d_name) != ".." && string(epdf->d_name) != "." ) : (epdf->d_type==DT_DIR && strstr(epdf->d_name,"..") == NULL && strstr(epdf->d_name,".") == NULL ) ){
                recurseDir(avl, path+epdf->d_name+"/",files, showHiddenDirs);
            }
            if(epdf->d_type==DT_REG){
                
                avl.parseFileInsert(path+epdf->d_name);
                //hashy.parseFileInsert(path+epdf->d_name);
                //cout << "parsed a file." << endl;
            }
        }
    }
    closedir(dpdf);
}



int main(){
	//Start of Project
	//create a new text file
	
	AVL avl;
	TFT tft;
	
	int userInput;
	bool loop = true;

	string path = "test/";
	vector<string> files;

	recurseDir(avl, path, files, false);

	avl.printTree();

	while (loop)
	{
		cout << "Enter a number to preform functionality" << endl;
		cout << "1 = search" << endl
			<< "2 = insert" << endl
			<< "3 = delete" << endl
			<< "4 = sort"   << endl
			<< "5 = range search" << endl
			<< "6 = quit program" << endl; 
		cin >> userInput;

		
		
		if(userInput == 1 || 2 || 3 || 4 || 5 )
		{
			switch(userInput)
			{
				case 1 :
					{
						/*cout << "You selected to search" << endl
							<< "PLease type a word to search" << endl;*/
						string Input;
						cin >> Input;
						avl.search(Input);

						//AVL search function
						//timing fucntions to clock speed of functions
						clock_t time_req_AVL;
						time_req_AVL = clock();

						time_req_AVL = clock() - time_req_AVL;
						/*
						for(int k=0; k<100; k++)
						{
							avl.search(Input); 
						}*/
						avl.search(Input);

						//Hash search function
						clock_t time_req_Hash;
						time_req_Hash = clock();

						/*
						for(int k=0; k<100; k++)
						{
							myHash.search(Input);
						}*/

						time_req_Hash = clock() - time_req_Hash;

						//print timing values of functions
						cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
						//cout << "Hash: " << (float)time_req_Hash/CLOCKS_PER_SEC << "s" << endl;*/
						break;
					}

				case 2 :
					{
						/*cout << "You selected to insert" << endl
							<< "Please type a word to insert" << endl;*/
						string Input;
						cin >> Input;

						//AVL insert function
						clock_t time_req_AVL;
						time_req_AVL = clock();
/*
						for(int k=0; k<100; k++){
							avl.insert(Input);
						}*/
						avl.insert(Input);
						time_req_AVL = clock() - time_req_AVL;
						

						//Hash insert function
						clock_t time_req_Hash;
						time_req_Hash = clock();

						/*
						for(int k=0; k<100; k++){
							myHash.insert(Input);
						}*/
						time_req_Hash = clock() - time_req_Hash;

						//print timing values of functions
						cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
						//cout << "Hash: " << (float)time_req_Hash/CLOCKS_PER_SEC << "s" << endl;

						break;
					}

				case 3 :
					{
						/*cout << "You selected to delete" << endl
							<< "Please type a word to delete" << endl;*/
						string Input;
						cin >> Input;

						//AVL deleteOne function
						clock_t time_req_AVL;
						time_req_AVL = clock();
						for(int k=0; k<100; k++){
							avl.deleteOne(Input);
						}
						time_req_AVL = clock() - time_req_AVL;

						//Hash deleteOne function
						clock_t time_req_Hash;
						time_req_Hash = clock();
						/*
						for(int k=0; k<100; k++){
							myHash.deleteOne(Input);
						}*/
						time_req_Hash = clock() - time_req_Hash;

						//print timing values of functions
						cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
						//cout << "Hash: " << (float)time_req_Hash/CLOCKS_PER_SEC << "s" << endl;

						break;
					}

				case 4 :
					{
						/*cout << "You selected to sort" << endl;*/
			
						//AVL deleteOne function
						clock_t time_req_AVL;
						time_req_AVL = clock();

						
						avl.lexSort();
					
						time_req_AVL = clock() - time_req_AVL;


						//Hash deleteOne function
						clock_t time_req_Hash;
						time_req_Hash = clock();

						
						//myHash.lexSort();
					
						time_req_Hash = clock() - time_req_Hash;

						//print values of timing functions
						cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
						//cout << "Hash: " << (float)time_req_Hash/CLOCKS_PER_SEC << "s" << endl;

						break;
					}
				
				case 5 :
					{
					
						cout << "You selected to range search" << endl
							<< "Please type your first word to Range search" << endl;
						
						string Input1;
						cin >> Input1;
						//cout << "Please type your second word to Range search" << endl;
						string Input2;
						cin >> Input2;
						
						//AVL rangeSearch function
						clock_t time_req_AVL;
						time_req_AVL = clock();

						avl.rangeSearch(Input1, Input2);
						time_req_AVL = clock() - time_req_AVL;

						//Hash rangeSearch function
						clock_t time_req_Hash;
						time_req_Hash = clock();

						
						//myHash.rangeSearch(Input1, Input2);

						time_req_Hash = clock() - time_req_Hash;

						//print values of timing functions
						cout << "AVL: " << (float)time_req_AVL/CLOCKS_PER_SEC << "s" << endl;
						//cout << "Hash: " << (float)time_req_Hash/CLOCKS_PER_SEC << "s" << endl;

						break;
						
					}
				
			}

		}
		else
		{
			cout << "Incorrect number, please try again" << endl;
			loop = false;
		}
    
	}
	/*Instructions:
	 * Parse a file and remove unwanted characters
	 * 	Ignore all stopwords and non alphabetical texts
	 * 	Words should not be case sensative
	 * Insert Each word using the insert function for AVL AND HT
	 */
return 0;
}