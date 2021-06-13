#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include "UnsortedArray.cpp"
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

void open()
{
   
}

int main()
{
    UnsortedArray a;
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
                        a.add(word);
                    }
                }
            }
        }
        myfile.close();
        //a.print();
        a.find("The");
        a.find("i");
        a.find("asdasd");
    }
    else
    {
        cout << ":;;;";
    }

    return 0;
}