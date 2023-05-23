#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <chrono>
#include <cctype>
#include <string.h>
#include "UnsortedArray.cpp"
#include "HashMap.cpp"
#include "BinaryTree.cpp"
using namespace std;

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

string showTime(string format, chrono::steady_clock::time_point start, chrono::steady_clock::time_point end)
{
    string returnString = "Ellasped time in ";
    if (format == "ms")
    {
        int time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        returnString = returnString + to_string(time) + "milisseconds: " + "ms\n";

        return returnString;
    }
    if (format == "ns")
    {
        int time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        returnString = returnString + to_string(time) + "nanosecods: "  + "ns\n";

        return returnString;
    }
    if (format == "sec")
    {
        int time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        returnString = returnString + to_string(time) + "seconds: "+ "sec\n";

        return returnString;
    }

    return "";
}

int main()
{
    const string TIME_FORMAT = "ms", INPUT_FILE_NAME = "small-file.txt", OUTPUT_FILE_NAME = "output.txt";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(INPUT_FILE_NAME);
    outputFile.open(OUTPUT_FILE_NAME);

    if (!outputFile.is_open()){
        cout << "Could not open \"output.txt\"";
        return 1;
    }

    if (!inputFile.is_open()){
        outputFile << "Could not open \"small-file.txt\"";
        return 1;
    }

    chrono::steady_clock::time_point end, start;

    string Q[1000];
    string previousWord, currentWord, line, pair;

    int  QsetCounter = 0;
    srand(time(0));
    UnsortedArray unsortedArray;
    HashMap hashMap;
    BinaryTree binaryTree;
    
    while (getline(inputFile,line))
    {
        if (!line.empty()){
            istringstream stringStream(removeAnnotation(line));
            stringStream >> previousWord;

            while ( stringStream >> currentWord){
                pair = previousWord + " " + currentWord;

                unsortedArray.insert(pair);
                //  binaryTree.insert(pair);

                hashMap.insert(pair);

                previousWord = currentWord;

                if (QsetCounter <1000){
                    int randomNumber = rand();
                    if (randomNumber % 10 >7){
                        Q[QsetCounter] = pair;
                        QsetCounter++;
                    }
                }       
            }
        }
    }   
    
    inputFile.close();   
    
    // UnsortedArray
    
        outputFile << endl
            << "          UnsortedArray " << endl
            << "~~~~~~~~~~~~~~~~~~~~~~" << endl;

        start = chrono::steady_clock::now();
        for (string q : Q)
        {
            outputFile << unsortedArray.find(q);
        }
        end = chrono::steady_clock::now();
        outputFile << showTime(TIME_FORMAT, start, end); 

        //Hashmap
        outputFile << endl
                << "          HashMap " << endl
                << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        start = chrono::steady_clock::now();
        for (string q : Q)
        {
            outputFile << hashMap.get(q);
        }
        end = chrono::steady_clock::now();
        outputFile << showTime(TIME_FORMAT, start, end);
    
        // BST
        /*   cout << endl
                << "          BinarySearchTree " << endl
                << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

           start = chrono::steady_clock::now();
           for (string q : Q)
           {
               binaryTree.find(q);
           }
           end = chrono::steady_clock::now();
           showTime(TIME_FORMAT, start, end); */
        outputFile.close();

    return 0;
}