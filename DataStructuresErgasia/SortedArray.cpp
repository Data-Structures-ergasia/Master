#include "SortedArray.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include "Constants.h"

using namespace constants;
using namespace std;


SortedArray::SortedArray()
{
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now(); 
    chrono::milliseconds totalElapsedTime(0); 

    capacity = ARRAY_SIZE;
    size = 0;
    array = new (nothrow) entry*[capacity];

    for (long long int i = 0 ; i < capacity ; i++){
        array[i] = new entry();
    }

    if (array == NULL)
    {
        cout << NOT_ENOUGH_MEMORY;
    }

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::milliseconds elapsedTime = chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        
    totalElapsedTime += elapsedTime;
}

SortedArray::~SortedArray()
{
    for (long long int i = 0 ; i < capacity ; i++){
        delete array[i];
    }

    delete[] array;
}

string SortedArray::getBuildingTime(){
    string returnString = BUILDING_TIME;

    if (SORTED_ARRAY_BUILD_TIME_UNIT == MS)
    {
        int time = std::chrono::duration_cast<chrono::milliseconds>(totalElapsedTime).count();
        returnString = returnString  + MILLISECONDS + to_string(time) + MS + NEWLINE;

        return returnString;
    }
    if (SORTED_ARRAY_BUILD_TIME_UNIT == NS)
    {
        int time = std::chrono::duration_cast<chrono::nanoseconds>(totalElapsedTime).count();
        returnString = returnString  + NANOSECONDS + to_string(time) + NS + NEWLINE;

        return returnString;
    }
    if (SORTED_ARRAY_BUILD_TIME_UNIT == SEC)
    {
        int time = std::chrono::duration_cast<chrono::seconds>(totalElapsedTime).count();
        returnString = returnString  + SECONDS + to_string(time) + SEC + NEWLINE;

        return returnString;
    }
    return EMPTY;
}

int SortedArray::compare(string s1, string s2){
    return s1.compare(s2);
}

string SortedArray::find(string key)
{
    string returnString = KEY + key + RIGHT_QUOTATION_MARK;

    long long int position = findPositionOf(key);

    int compar = compare(array[position] -> key, key);

    if (compar == 0){
        returnString += WAS_FOUND + to_string(array[position] -> found) + TIMES + NEWLINE;
        return returnString;
    }

     returnString += WAS_NOT_FOUND + NEWLINE;
     return returnString;
}

long long int SortedArray::findPositionOf(string key){
    long long int low = 0;
    long long int high = size - 1;
    long long int mid;
    int comparison;

    while (low <= high) {
        mid = low + (high - low) / 2;

        comparison = compare(array[mid] -> key, key);

        if (comparison == 0)
        {
            return mid;
        } else if (comparison < 0) {
            low = mid + 1;

        } else {
            high = mid - 1;
        }

    }

    comparison = compare(array[mid] -> key, key);
    if (comparison < 0 ){
        mid = mid + 1;
    }

    return mid;
}              

void SortedArray::insert(string key){
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    if (size == 0){
        array[0] -> found = 1;
        array[0] -> key = key;

        size++;

        return;
    }

    if (size + 1 == capacity){
        resize();
    }

    long long int position = findPositionOf(key);

    //shift elements to the right
    int comparison = compare(array[position] -> key, key);
    if (comparison == 0 ){
        array[position] -> found ++;
        return;
    }

    size++;

    for (long long int i = size - 1 ; i > position ; --i){
        array[i] -> key  = array[i - 1] -> key;
        array[i] -> found = array[i - 1] -> found;

    }

    array[position] -> found = 1;
    array[position] -> key = key;

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        
    totalElapsedTime += elapsedTime;
}

string SortedArray::get(long long int i){
    return array[i] -> key + " was found: " +  to_string(array[i] -> found) + NEWLINE;
}

long long int SortedArray::getSize(){
    return size;
}

void SortedArray::resize(){
    long long int newCapacity = capacity + capacity/2 ;
    long long int oldCapacity = capacity;

    capacity = newCapacity;

    entry **temp = new (nothrow) entry*[newCapacity];

    for (long long int i = 0 ; i < capacity ; i++){
        temp[i] = new entry();
    }

    if (temp != NULL)
    {
        for (long long int i = 0; i < size ; i++){
            temp[i] -> key = array[i] -> key;
            temp[i] -> found = array[i] -> found;
        }

        // delete each pointer of the array and then the array as a whole to save space
        for (long long int i = 0 ; i < oldCapacity ; i++){
            delete array[i];
        }

        delete [] array;

        array = temp;
        cout << "new capacity : " << capacity << endl;
    }
    else
    {
        cout << NOT_ENOUGH_MEMORY_TO_RESIZE << NEWLINE;
        exit(1);
    }
}