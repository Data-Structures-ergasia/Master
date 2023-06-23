#include "UnsortedArray.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include "Constants.h"

using namespace constants;
using namespace std;

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

UnsortedArray::~UnsortedArray()
{
    for (size_t i = 0 ; i < capacity ; i++){
        delete array[i];
    }

    delete[] array;
}

int UnsortedArray::compare(string s1, string s2){
    return s1.compare(s2);
}

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
            insertIntoTable(temp, array[i] -> key, array[i] -> found);
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

void UnsortedArray::insertIntoTable(entry** tableToInsertTo, string key, unsigned int found){
    for (size_t i = 0; i < size; i++)
    {
        if (compare(tableToInsertTo[i] -> key, key) == 0)
        {
            tableToInsertTo[i] -> found ++;
            return;
        }
    }

    tableToInsertTo[size] -> key = key;
    tableToInsertTo[size] -> found = found;
    size++;
}

void UnsortedArray::insertIntoTable(entry** tableToInsertTo, string key){
    for (size_t i = 0; i < size; i++)
    {
        short compare = tableToInsertTo[i] -> key.compare(key);
        if (compare == 0)
        {
            tableToInsertTo[i] -> found ++;
            return;            
        }
    }
    
    tableToInsertTo[size] -> key = key;
    tableToInsertTo[size] -> found = 1;
    size++;
}

void UnsortedArray::insert(string key)
{
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now(); 

    if (size >= capacity){
        resize();
    }

    insertIntoTable(array,key);
    
    calculateTime(startTime);
}
