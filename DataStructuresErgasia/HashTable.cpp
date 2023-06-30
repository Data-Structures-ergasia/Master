#include "HashTable.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <string>
#include "Constants.h"

using namespace constants;
using namespace std;

//constructor, initialize pointers for all elements
HashTable::HashTable(){
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

// compare the two strings, s1: existing key, s2: key to insert
int HashTable::compare(string s1, string s2){
    return s1.compare(s2);
}

// calculate time passed in nanosecods (better accuracy)
void HashTable::calculateTime(chrono::steady_clock::time_point startTime){
    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::nanoseconds elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    totalElapsedTime += elapsedTime;
}


// delete each pointer of the array and then the array as a whole
HashTable::~HashTable(){
    for (size_t i = 0 ; i < capacity ; i++){
        delete array[i];
    }

    delete[] array;
}

// resize the table by capacity/2, each element is re inserted to its new position
void HashTable::resize()
{
    size_t newCapacity = capacity + capacity/2 ;
    size_t oldCapacity = capacity;

    capacity = newCapacity;

    //initialize the new table
    entry **temp = new (nothrow) entry*[newCapacity];
    for (size_t i = 0 ; i < capacity ; i++){
        temp[i] = new entry();
    }

    size = 0;

    if (temp != NULL){

        for (size_t i =0 ; i < oldCapacity ; i++){
            // insert each element along with the times it was found by this point
            insertIntoTable(temp, array[i] -> key, array[i] -> found);
        }

        // delete each pointer of the array and then the array as a whole to save space
        for (size_t i = 0 ; i < oldCapacity ; i++){
            delete array[i];
        }

        delete [] array;

        array = temp;
    }
    else
    {
        cout << NOT_ENOUGH_MEMORY_TO_RESIZE << endl;
        exit(1);
    }
}

// primary hashing function, for each letter of the key we multiply by a prime number ie 31 and add the letter's value, then
// take mod capacity to ensure we won't get a value that is out of bounds
size_t HashTable::hash(string key){
    size_t hashValue = 0;
    for (unsigned int i = 0 ; i < key.size(); i++ ){
        hashValue = hashValue * 31 + key[i];
    }

    return hashValue % capacity;
}

// secondary hashing function, get the next position
size_t HashTable::hash2(size_t position){
    return (position + 1) % capacity;
}

// used when resizing to keep track of the times the element was found,
// get the index of the key
// if there is another element, go to the next position, until an empty space is found
void HashTable::insertIntoTable(entry** tableToInsertTo, string key, unsigned int found){
    size_t position = hash(key);

    while (tableToInsertTo[position] -> occupied) {

        // the key at position is the same as the one that is being inserted
        if (compare(tableToInsertTo[position] -> key, key) == 0){
            tableToInsertTo[position] -> found++;
            return;
        }

        position = hash2(position);
    }

    // the key wasn't found, add it to the array with its found counter
    tableToInsertTo[position] -> key = key;
    tableToInsertTo[position] -> found = found;
    tableToInsertTo[position] -> occupied = true;

    size++;
}

// insert element to the table using the hash functions
void HashTable::insert(string key){

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    // if the array is LOAD_FACTOR% (by default 75%) full, increace its size to avoid collisions
    if (size >capacity * LOAD_FACTOR){
        resize();
    }

    size_t position = hash(key);

    while (array[position] -> occupied) {
        // the key at position is the same as the one that is being inserted
        if (compare(array[position] -> key, key) == 0){
            array[position] -> found++;
            array[position] -> key = key;
            return;
        }
        position = hash2(position);
    }

    // the key wasn't found, add it to the array
    array[position] -> key = key;
    array[position] -> found = 1;
    array[position] -> occupied = true;

    size++;

    calculateTime(startTime);
}

// get the string in question
// search the array using the primary hash function, if the key is not found, use the secondary
// if the the position index takes the same value as the initial, the key is not found and most likely
// the whole array was iterated
// returns a string that is printed to the output file
string HashTable::get(string key){
    string returnString = KEY + key + RIGHT_QUOTATION_MARK;

    size_t position = hash(key);
    size_t initialPosition = position;

    while (array[position] -> occupied){
        if (compare(array[position] -> key, key) == 0){
            returnString += WAS_FOUND + to_string(array[position] -> found) + TIMES + NEWLINE;
            return returnString;
        }

        position = hash2(position);

        if (position == initialPosition) {
            returnString +=  WAS_NOT_FOUND + NEWLINE;
            return returnString;
        }
    }

    returnString +=  WAS_NOT_FOUND + NEWLINE;
    return returnString;
}

// return the time it took for building the structure, i.e. inserting the keys and initializing the array
string HashTable::getBuildingTime(){
    string returnString = BUILDING_TIME;

    if (HASH_TABLE_BUILD_TIME_UNIT == MS)
    {
        int time = chrono::duration_cast<chrono::milliseconds>(totalElapsedTime).count();
        returnString = returnString  + MILLISECONDS + to_string(time) + MS + NEWLINE;

        return returnString;
    }

    if (HASH_TABLE_BUILD_TIME_UNIT == NS)
    {
        int time = chrono::duration_cast<chrono::nanoseconds>(totalElapsedTime).count();
        returnString = returnString  + NANOSECONDS + to_string(time) + NS + NEWLINE;

        return returnString;
    }

    if (HASH_TABLE_BUILD_TIME_UNIT == SEC)
    {
        int time = chrono::duration_cast<chrono::seconds>(totalElapsedTime).count();
        returnString = returnString  + SECONDS + to_string(time) + SEC + NEWLINE;

        return returnString;
    }
    return EMPTY;
}

