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
    int c = 0;
    srand(time(0));
    UnsortedArray a;
    HashMap h;
    BinaryTree b;
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

                        if (c < 1000)
                        {
                            int randomNumber = rand();
                            if (randomNumber % 10 > 7)
                            {
                                Q[c] = word;
                                c++;
                            }
                        }
                     //   a.insert(word);
                      //  b.insert(word);
                     //   h.insert(word);
                    }
                }
            }
        }
        myfile.close();

        b.insert("hi");
        b.insert("bs");
        b.insert("se");
        b.insert("ab");
        b.insert("hf");

        b.inorder();
        b.postorder();
        b.preorder();

   /*     cout << endl
             << "          UnsortedArray " << endl
             << "~~~~~~~~~~~~~~~~~~~~~~" << endl;

        start = chrono::steady_clock::now();
        for (string q : Q)
        {
            a.find(q);
        }
        showTime(TIME_FORMAT, start, end);

        cout << endl
             << "          HashMap " << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        start = chrono::steady_clock::now();
        for (string q : Q)
        {
            h.get(q);
        }
        end = chrono::steady_clock::now();
        showTime(TIME_FORMAT, start, end);

        cout << endl
             << "          BinarySearchTree " << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        start = chrono::steady_clock::now();
        for (string q : Q)
        {
            b.find(q);
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