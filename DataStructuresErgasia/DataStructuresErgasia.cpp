#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
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
        else if (c == ' ')
        {
            word = word + c;
        }
    }
    return word;
}

int main()
{
    string word, line;
    ifstream myfile;
    myfile.open("small-file.txt");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (!line.empty())
            {
                line = removeAnnotation(line);
                stringstream stringstream(line);
                while (getline(stringstream, word, ' '))
                {
                    cout << word << "\n";
                }
            }
                }

        myfile.close();
    }
    else
    {
        cout << ":;;;";
    }

    return 0;
}