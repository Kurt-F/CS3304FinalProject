#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
#include <cmath>
#include "LinkedList.cpp"
#include "BinaryTree.cpp"
#include "SkipList.cpp"
/**********************************************************************************************************
*   TestCases.cpp
*   Kurt Floyd
*   CS 3304
*   11/11/2017
*
*   All data structures are implemented with add() functions that take a key as well as a value. This
*       is to enable them to work as dictionaries, as well as eliminate the possibility that the generic 
*       type T supplied by the user could be undefined for comparison operations. Searching and removal are
*       implemented using keys, not values.
*   Each test times each interval of insertion/deletion and adds the interval length and the time to a 
*       string called "output," which is then printed as a csv file.
*
***********************************************************************************************************/

//The maximum number of iterations for all tests, set to a lower number if need be.
int const iterSize = 10000;
//How much the test functions increase the interval each iteration.
int const step = 10;

//Helper function that writes a preformatted string (s) to file with the associated filename (n)
void writeToFile(string s, string n){
    ofstream file;
    //Change the filename from a string to a char array
    const char* name = n.c_str();
    //Open the file
    file.open(name);
    //Write to file
    file << s;
    //Close the file
    file.close();
}


/*
*	Randomly inserts increasing numbers of random integers
*
*/
void insertTest(){
        srand(time(NULL));
        /*
        * Insert increasingly large sets of random integers into a binary tree
        */
        //Set the name of the file to store the timing output in.
        string outputName = "BST_int.csv";
        //Initialise and declare output string
        string output = "";
        //Initialise and declare a counter
        int n = 0;
        //Initialise and declare a tree for sorting
        BinaryTree<int>* tree = new BinaryTree<int>();
        //loop up to itersize
        while(n < iterSize){
            //Increment the interval every iteration
            n+=step;
            //Start timing
            clock_t t0 = clock();
            //Make n additions
            for(int i = 0; i < n; i++){
                tree->add(rand(),rand());
            }
            //stop timing
            clock_t t1 = clock();
            //Get the time elapsed
            double t = double(t1 - t0) / CLOCKS_PER_SEC;
            //Convert time and number of additions to string
            string N = to_string(n);
            string T = to_string(t);
            //Insert a line into our output string
            output = output + N + "," + T + ",\n";
            //Delete the now useless tree and create a new empty one, to avoid memory problems
            delete tree;
            tree = new BinaryTree<int>();
        }
        cout << endl;
        //The BST is no longer needed.
        delete tree;
        //Write our timing data (output) to file
        writeToFile(output, outputName);
        std::cout << "Binary Tree insertion testing finished, output is in " << outputName << endl;
        output = "";

        /*
        * Insert increasingly large sets of random integers into a skiplist
        */
        n = 0;
        outputName = "SkipList_int.csv";
        SkipList<int>* slist = new SkipList<int>(log2(iterSize)*2, 0);  
        while(n < iterSize){
            n+=step;
            clock_t t0 = clock();           
            for(int i = 0; i < n; i++)
                slist->add(rand(),rand());
            clock_t t1 = clock(); 
            double t = double(t1 - t0) / CLOCKS_PER_SEC;
            //Convert time and number of additions to string
            string N = to_string(n);
            string T = to_string(t);
            //Insert a line into our output string
            output = output + N + "," + T + ",\n";
            delete slist;
            slist = new SkipList<int>(log2(n)*2, 0);
        }
        writeToFile(output, outputName);
        std::cout << "Skip List insertion testing finished, output is in " << outputName << endl;
        output = "";
        delete slist;

        /*
        * Insert increasingly large sets of random integers into a linked list
        */
        n = 0;
        outputName = "LinkedList_int.csv";
        LinkedList<int>* llist = new LinkedList<int>();
        while(n < iterSize){
            cout << n << endl;
            n+=step;
            clock_t t0 = clock();  
            for(int i = 0; i < n; i++){
                llist->add(rand(),rand());
            }
            clock_t t1 = clock(); 
            //Find the clocks elapsed, and convert to seconds
            double t = double(t1 - t0) / CLOCKS_PER_SEC;
             //Convert time and number of additions to string
            string N = to_string(n);
            string T = to_string(t);
            //Insert a line into our output string
            output = output + N + "," + T + ",\n";
            delete llist;
            llist = new LinkedList<int>();
        }
        writeToFile(output, outputName);
        std::cout << "Linked List insertion testing finished, output is in " << outputName << endl;
        delete llist;
	}

//Test the time it takes to delete nodes
void deleteTest(){
    SkipList<int>* list = new SkipList<int>(2 * log2(iterSize),0);
    string output = "";
    string outputName = "deleteTest_sl.csv";
    //Populate a list with itersize^2 values
    for(int i = 0; i < iterSize; i++){
        list->add(rand()%iterSize*iterSize, i);
    }

    for(int n = 0; n < iterSize; n+= step){
        clock_t t0 = clock();  
        for(int i = 0; i < n; i++)
            list->remove(i);
        clock_t t1 = clock(); 
        double t = double(t1 - t0) / CLOCKS_PER_SEC;
        //Convert time and number of additions to string
        string N = to_string(n);
        string T = to_string(t);
        //Insert a line into our output string
        output = output + N + "," + T + ",\n";
    }
    writeToFile(output, outputName);
    std::cout << "Skip List removal testing finished, output is in " << outputName << endl;


    
}


//Test each data structure with sequences of objects
//Used for determining whether to insert or remove values. Not a real coinflip, biased towards insertion.
bool coinFlip(){
    srand(time(NULL));
    //Squash the random number between 0 and 1. 
    double num = rand()/RAND_MAX;
    if(num > 0.6)
        return true;
    return false;
    }
