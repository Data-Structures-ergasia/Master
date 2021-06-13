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
            cout << array[i].key << " was found " << array[i].found << " times." << endl;
            return;
        }
    }
    cout << key << " was not found!";
}

short UnsortedArray::exists(string key)
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

void UnsortedArray::resize()
{
    cout << "Resizing . . . " << endl;
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

void UnsortedArray::add(string key)
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
    size = 1000;
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
        cout << array[i].key << " was found " << array[i].found << " times." << endl;
    }
}
