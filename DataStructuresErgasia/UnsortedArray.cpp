#include "UnsortedArray.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include "Constants.h"

using namespace constants;
using namespace std;

//constructor, initialize pointers for all elements
UnsortedArray::UnsortedArray()
{
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
    chrono::nanoseconds totalElapsedTime(0);

    capacity = ARRAY_SIZE;
    size = 0;
    array = new (nothrow) entry*[capacity];

    for (size_t i = 0 ; i < capacity ; i++){
        array[i] = new entry();
    }

    if (array == NULL)
    {
        cout << NOT_ENOUGH_MEMORY;
    }

    calculateTime(startTime);
}

// delete each pointer of the array and then the array as a whole
UnsortedArray::~UnsortedArray()
{
    for (size_t i = 0 ; i < capacity ; i++){
        delete array[i];
    }

    delete[] array;
}

// compare the two strings, s1: existing key, s2: key to insert
int UnsortedArray::compare(string s1, string s2){
    return s1.compare(s2);
}

// calculate time passed in nanosecods (better accuracy)
void UnsortedArray::calculateTime(chrono::steady_clock::time_point startTime){
    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::nanoseconds elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    totalElapsedTime += elapsedTime;
}

string UnsortedArray::getBuildingTime(){
    string returnString = BUILDING_TIME;

    if (UNSORTED_ARRAY_BUILD_TIME_UNIT == MS)
    {
        int time = std::chrono::duration_cast<chrono::milliseconds>(totalElapsedTime).count();
        returnString = returnString  + MILLISECONDS + to_string(time) + MS + NEWLINE;

        return returnString;
    }
    if (UNSORTED_ARRAY_BUILD_TIME_UNIT == NS)
    {
        int time = std::chrono::duration_cast<chrono::nanoseconds>(totalElapsedTime).count();
        returnString = returnString  + NANOSECONDS + to_string(time) + NS + NEWLINE;

        return returnString;
    }
    if (UNSORTED_ARRAY_BUILD_TIME_UNIT == SEC)
    {
        int time = std::chrono::duration_cast<chrono::seconds>(totalElapsedTime).count();
        returnString = returnString  + SECONDS + to_string(time) + SEC + NEWLINE;

        return returnString;
    }
    return EMPTY;
}

// find the string in question
// search the array linearly,
// returns a string that is printed to the output file
string UnsortedArray::find(string key)
{
    string returnString = KEY + key + RIGHT_QUOTATION_MARK;

    for (size_t i = 0; i < size; i++)
    {
        if (compare(array[i] -> key, key) == 0)
        {
            returnString += WAS_FOUND + to_string(array[i] -> found) + TIMES + NEWLINE;
            return returnString;
        }
    }
    returnString += WAS_NOT_FOUND + NEWLINE;
    return returnString;
}

// resize the table by capacity/2, each element is re inserted to its new position
void UnsortedArray::resize()
{
    size_t newCapacity = capacity + capacity/2 ;
    size_t oldCapacity = capacity;

    capacity = newCapacity;
    size = 0;

    entry **temp = new (nothrow) entry*[newCapacity];

    for (size_t i = 0 ; i < capacity ; i++){
        temp[i] = new entry();
    }

    if (temp != NULL)
    {
        for (size_t i = 0; i < oldCapacity ; i++){
            temp[i] -> key = array[i] -> key;
            temp[i] -> found = array[i] -> found;
        }

        for (size_t i = 0 ; i < oldCapacity ; i++){
            delete array[i];
        }

        delete [] array;

        array = temp;

    }
    else
    {
        cout << NOT_ENOUGH_MEMORY_TO_RESIZE << NEWLINE;
        exit(1);
    }
}

// insert the key in question to the array, use linear search to check whether it exists or not
void UnsortedArray::insert(string key)
{
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    if (size >= capacity){
        resize();
    }

    for (size_t i = 0; i < size; i++)
    {
        if (compare(array[i] -> key, key) == 0)
        {
            array[i] -> found ++;
            return;
        }
    }

    array[size] -> key = key;
    array[size] -> found = 1;
    size++;

    calculateTime(startTime);
}
