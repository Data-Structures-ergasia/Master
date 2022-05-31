#include "UnsortedArray.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

void UnsortedArray::find(string key)
{
    string word = "";
    for (char c : key)
    {
        c = tolower(c);
        word = word + c;
    }

    for (int i = 0; i < counter; i++)
    {
        if (array[i].key == word)
        {
            cout << "\"" << array[i].key << "\" was found " << array[i].found << " times." << endl;
            return;
        }
    }
    cout << "'" << key << "' was not found!";
}

int UnsortedArray::exists(string key)
{
    for (int i = 0; i < counter; i++)
    {
        if (array[i].key == key)
        {
            //cout << key << " exists" << endl;
            return i;
        }
    }
    return -1;
}

void UnsortedArray::deleteKey(string key)
{
    int pos = exists(key);
    if (pos != -1)
    {
        entries temp = array[counter - 1];
        array[counter - 1] = array[pos];
        array[pos] = temp;
        array[counter - 1].found = 0;
        array[counter - 1].key = "";
    }
}

void UnsortedArray::resize()
{
    int newSize = size + 250;
    size = newSize;
    entries *newArray = new (nothrow) entries[newSize];
    if (newArray != NULL)
    {
        entries *temp = array;
        array = newArray;
        for (int i = 0; i < counter; i++)
        {
            array[i] = temp[i];
        }
        delete[] temp;
    }
    else
    {
        cout << "There was not enough memory to resize!" << endl;
        exit(1);
    }
}

void UnsortedArray::insert(string key)
{
    int position = exists(key);
    if (position == -1)
    {
        if (counter >= size)
        {
            resize();
        }

        //cout << "Adding : " << key << endl;
        array[counter].key = key;
        array[counter].found = 1;
        counter++;
    }
    else
    {
        array[position].found++;
    }
}

UnsortedArray::UnsortedArray()
{
    size = 3000;
    counter = 0;
    array = new (nothrow) entries[size];
    if (array == NULL)
    {
        cout << "Not enough Memory";
    }
}
UnsortedArray::~UnsortedArray()
{
    delete[] array;
}

void UnsortedArray::print()
{
    cout << "Printing . . . " << endl;
    for (int i = 0; i < counter; i++)
    {
        if (array[i].found)
        {
            cout << array[i].key << " was found " << array[i].found << " times." << endl;
        }
    }
}
