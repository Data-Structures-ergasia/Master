#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <chrono>
#include <string.h>
#include "UnsortedArray.h"
#include "UnsortedArray.cpp"
#include "SortedArray.h"
#include "SortedArray.cpp"
#include "HashTable.h"
#include "HashTable.cpp"
#include "BinaryTree.h"
#include "BinaryTree.cpp"
#include "AVl.h"
#include "Avl.cpp"
#include "Constants.h"

using namespace std;
using namespace constants;


/*
    this function removes annotation from a given string by parsing each character and checking if it is alphanumeric or space.
    the alphanumeric characters are set to lowercase
*/
string removeAnnotation(string str)
{
    string line = "";
    for (char c : str)
    {
        if (isalpha(c))
        {
            line += tolower(c);
        }
        else if (isspace(c)){
            line += c;
        }

    }
    return line;
}


/*
    this function calculates and prints the time in different formats, needed for each structure to find the given keys
*/
string showTime(chrono::steady_clock::time_point start, chrono::steady_clock::time_point end, string format)
{
    string returnString = ELLAPSED_TIME_IN;

    if (format == MS)
    {
        int time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        returnString = returnString  + MILLISECONDS + to_string(time) + MS + NEWLINE;

        return returnString;
    }
    if (format == NS)
    {
        int time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        returnString = returnString  + NANOSECONDS + to_string(time) + NS + NEWLINE;

        return returnString;
    }
    if (format == SEC)
    {
        int time = chrono::duration_cast<chrono::seconds>(end - start).count();
        returnString = returnString  + SECONDS + to_string(time) + SEC + NEWLINE;

        return returnString;
    }
    return EMPTY;
}

/*
    Add the name of each datstructure before its results
*/
string printHeadLine(string title){
    string headLine = HEADLINE_FIRST_PART + title + HEADLINE_SECOND_PART;
    return headLine;
}

/*
    Search the avl tree for the pairs in question, results to output file
*/
void searchAVLTree(Avl* avl, ofstream &outputFile, string (&Q)[Q_SIZE]){
    chrono::steady_clock::time_point end, start;
    outputFile << printHeadLine(AVL_TREE);
    outputFile << avl -> getBuildingTime();

    start = chrono::steady_clock::now();
    for (string q : Q)
    {
        outputFile << avl -> find(q);
    }
    end = chrono::steady_clock::now();

    outputFile << showTime(start, end, AVL_TREE_SEARCH_TIME_UNIT);
}

// /*
//     Search the binary tree for the pairs in question, results to output file
// */
void searchBinaryTree(BinaryTree* binaryTree, ofstream &outputFile, string (&Q)[Q_SIZE]){
    chrono::steady_clock::time_point end, start;
    outputFile << printHeadLine(BINARY_TREE);
    outputFile << binaryTree -> getBuildingTime();

    start = chrono::steady_clock::now();

    for (string q : Q)
    {
        outputFile << binaryTree -> find(q);
    }
    end = chrono::steady_clock::now();
    outputFile << showTime(start, end, BINARY_TREE_SEARCH_TIME_UNIT);
}

/*
    Search the hash table for the pairs in question, results to output file
*/
void searchHashTable(HashTable* hashTable, ofstream &outputFile, string (&Q)[Q_SIZE]){
    chrono::steady_clock::time_point end, start;
    outputFile << printHeadLine(HASH_TABLE);
    outputFile << hashTable -> getBuildingTime();

    start = chrono::steady_clock::now();
    for (string q : Q)
    {
        outputFile << hashTable -> get(q);
    }
    end = chrono::steady_clock::now();

    outputFile << showTime(start, end, HASH_TABLE_SEARCH_TIME_UNIT);
}

/*
    Search the unsorted array for the pairs in question, results to output file
*/
void searchUnsortedArray(UnsortedArray* unsortedArray, ofstream &outputFile, string (&Q)[Q_SIZE]){
        chrono::steady_clock::time_point end, start;
        outputFile << printHeadLine(UNSORTED_ARRAY);
        outputFile << unsortedArray -> getBuildingTime();
        start = chrono::steady_clock::now();

        for (string q : Q)
        {
            outputFile << unsortedArray -> find(q);
        }
        end = chrono::steady_clock::now();
        outputFile << showTime(start, end, UNSORTED_ARRAY_SEARCH_TIME_UNIT);
}

void searchSortedArray(SortedArray* sortedArray, ofstream &outputFile, string (&Q)[Q_SIZE]){
        chrono::steady_clock::time_point end, start;
        outputFile << printHeadLine(SORTED_ARRAY);
        outputFile << sortedArray -> getBuildingTime();
        start = chrono::steady_clock::now();

        int i =0;
        for (string q : Q)
        {
            outputFile << sortedArray -> find(q);
        }
        end = chrono::steady_clock::now();
        outputFile << showTime(start, end, SORTED_ARRAY_SEARCH_TIME_UNIT);
    }

int main()
{
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(INPUT_FILE_NAME);
    outputFile.open(OUTPUT_FILE_NAME);

    if (!outputFile.is_open()){
        cout << COULD_NOT_OPEN + OUTPUT_FILE_NAME;
        return 1;
    }

    if (!inputFile.is_open()){
        outputFile << COULD_NOT_OPEN + INPUT_FILE_NAME;
        return 1;
    }

    // if one of the files can not be opened then the programm stops.

    string Q[Q_SIZE];
    string previousWord, currentWord, line, pair;

    int  QsetCounter = 0;
    srand(time(0));

    //Avl avl;
    //BinaryTree binaryTree;
    //HashTable hashTable;
    //UnsortedArray unsortedArray;
    SortedArray sortedArray;

//  get each line of the file
    while (getline(inputFile,line))
    {
        if (!line.empty()){
            // if it is a non empty line, then we remove the annotations and get the first word
            istringstream stringStream(removeAnnotation(line));
            stringStream >> previousWord;

            // iterate each word of the line separated by space
            while ( stringStream >> currentWord){
                pair = previousWord + " " + currentWord;

               //avl.insert(pair);
               //binaryTree.insert(pair);
               //hashTable.insert(pair);
               //unsortedArray.insert(pair);
                sortedArray.insert(pair);

                previousWord = currentWord;

                // insert a word to Qset with an arbitary chance of 30%
                if (QsetCounter < Q_SIZE){
                    int randomNumber = rand();
                    if (randomNumber % 10 > 7){
                        Q[QsetCounter] = pair;
                        QsetCounter++;
                    }
                }
            }
        }
    }
    inputFile.close();

    chrono::steady_clock::time_point end, start;

    //searchAVLTree(&avl, outputFile, Q);
    //searchBinaryTree(&binaryTree, outputFile, Q);
    //searchHashTable(&hashTable, outputFile, Q);
    //searchUnsortedArray(&unsortedArray, outputFile, Q);
    searchSortedArray(&sortedArray, outputFile, Q);
   
    outputFile.close();

    return 0;
    }
