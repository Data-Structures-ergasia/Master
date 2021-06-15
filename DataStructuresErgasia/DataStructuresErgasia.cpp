#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <ctime>
#include "UnsortedArray.cpp"
#include "HashMap.cpp"
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

int main()
{
    string *Q = new string[1000];
    int c = 0;
    srand(time(0));
    UnsortedArray a;
    HashMap h;
    string tempWord, word, line;
    ifstream myfile;
    myfile.open("small-file.txt");
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

                        a.add(word);
                        h.insert(word);
                    }
                }
            }
        }
        myfile.close();

        cout << endl
             << " UnsortedArray " << endl
             << "~~~~~~~~~~~~~~~~~~~~~~" << endl;

        for (int i = 0; i < c; i++)
        {
            a.find(Q[i]);
        }
        cout << endl
             << " HashMap " << endl
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        for (int i = 0; i < c; i++)
        {
            h.get(Q[i]);
        }
    }
    else
    {
        cout << "Could not open file!";
    }

    return 0;
}