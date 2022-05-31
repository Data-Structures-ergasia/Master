#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <chrono>
#include "UnsortedArray.cpp"
#include "HashMap.cpp"
#include "BinaryTree.cpp"
using namespace std;

string removeAnnotation(string str)
{
    string word = "";
    for (char c : str)
    {
        if (isalpha(c))
        {
            word = word + c;
        }
        else
        {
            c = ' ';
            word = word + c;
        }
    }
    return word;
}

void showTime(string format, chrono::steady_clock::time_point start, chrono::steady_clock::time_point end)
{
    if (format == "ms")
    {
        cout << "Elapsed time in milliseconds: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count()
             << " ms" << endl;
        return;
    }
    if (format == "ns")
    {
        cout << "Elapsed time in nanoseconds: "
             << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
             << " ns" << endl;
        return;
    }
    if (format == "sec")
    {
        cout << "Elapsed time in seconds: "
             << chrono::duration_cast<chrono::seconds>(end - start).count()
             << " sec";
        return;
    }
}

int main()
{
    const string TIME_FORMAT = "ms", FILE_NAME = "small-file.txt";
    chrono::steady_clock::time_point end, start;
    string Q[1000];
    string pair = "";
    int pairCounter = 0, QsetCounter = 0;
    srand(time(0));
    UnsortedArray unsortedArray;
    HashMap hashMap;
    BinaryTree binaryTree;
    string tempWord, word, line;
    ifstream myfile;
    myfile.open(FILE_NAME);

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            //  cout<<line.length()<< "\n";
            if (!line.empty())
            {
                line = removeAnnotation(line);
                stringstream stringstream(line);
                // cout << "~~~~~~~~~~~~~~~~~" << line << endl;
                while (getline(stringstream, tempWord, ' '))
                {

                    if (!tempWord.empty())
                    {

                        string word = "";
                        for (char c : tempWord)
                        {
                            c = tolower(c);
                            word = word + c;
                        }
                        
                       
                        if (pairCounter == 0)
                        {
                            pair = word;
                        }
                        else if (pairCounter == 1)
                        {
                            pair = pair + " " + word;
                        }
                        pairCounter++;
                        if (pairCounter == 2)
                        {
                            // cout << "Pair = " << pair << "  counter = " << pairCounter << endl;
                            if (QsetCounter < 1000)
                            {
                                int randomNumber = rand();
                                if (randomNumber % 10 > 7)
                                {
                                    Q[QsetCounter] = pair;
                                    QsetCounter++;
                                }
                            }
                            // unsortedArray.insert(pair);
                            //  binaryTree.insert(pair);
                            hashMap.insert(pair);
                            pairCounter = 0;
                            pair = "";
                        }
                    }
                }
            }
        }
        myfile.close();

        // UnsortedArray
        /*
               cout << endl
                   << "          UnsortedArray " << endl
                   << "~~~~~~~~~~~~~~~~~~~~~~" << endl;

              start = chrono::steady_clock::now();
              for (string q : Q)
              {
                  unsortedArray.find(q);
              }
              end = chrono::steady_clock::now();
              showTime(TIME_FORMAT, start, end); */

        // Hashmap
        cout << endl
             << "          HashMap " << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        start = chrono::steady_clock::now();
        for (string q : Q)
        {
            hashMap.get(q);
        }
        end = chrono::steady_clock::now();
        showTime(TIME_FORMAT, start, end);

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
    }
    else
    {
        cout << "Could not open file!";
    }

    return 0;
}