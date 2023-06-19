#include "HashTable.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <string>
#include "Constants.h"

using namespace constants;
using namespace std;

HashTable::HashTable(){
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now(); 
    chrono::milliseconds totalElapsedTime(0); 

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

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::milliseconds elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        
    totalElapsedTime += elapsedTime;
}

HashTable::~HashTable(){
    for (size_t i = 0 ; i < capacity ; i++){
        delete array[i];
    }

    delete[] array;
}

void HashTable::resize()
{
    cout << "mpainw\n";
    size_t newCapacity = capacity + capacity/2 ;
    size_t oldCapacity = capacity;

    capacity = newCapacity;

    entry **temp = new (nothrow) entry*[newCapacity];

    for (size_t i = 0 ; i < capacity ; i++){
        temp[i] = new entry();
    }

    size = 0;
    
    if (temp != NULL){
        for (size_t i =0 ; i < oldCapacity ; i++){
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
        cout << NOT_ENOUGH_MEMORY_TO_RESIZE << endl;
        exit(1);
    }
}

size_t HashTable::hash(string key){
    size_t hashValue = 0;
    for (size_t i = 0 ; i < key.size(); i++ ){
        hashValue = hashValue * 31 + key[i];
    }
    
    return hashValue % capacity;
}


size_t HashTable::hash2(size_t position){
    return (position + 1) % capacity;
}

void HashTable::insertIntoTable(entry** tableToInsertTo, string key, unsigned int found){
    size_t position = hash(key);

    while (tableToInsertTo[position] -> occupied) {
        short compare = tableToInsertTo[position] -> key.compare(key);

        if (compare == 0){
            tableToInsertTo[position] -> found++;
            return; 
        }
        
        position = hash2(position);
    }

    tableToInsertTo[position] -> key = key;
    tableToInsertTo[position] -> found = found;
    tableToInsertTo[position] -> occupied = true;

    size++;
}

void HashTable::insertIntoTable(entry** tableToInsertTo, string key){
    size_t position = hash(key);

    while (tableToInsertTo[position] -> occupied) {
        short compare = tableToInsertTo[position] -> key.compare(key);
        if (compare == 0){
            tableToInsertTo[position] -> found++;
            tableToInsertTo[position] -> key = key; 
            return;
        }
        position = hash2(position);
    }


    tableToInsertTo[position] -> key = key;
    tableToInsertTo[position] -> found = 1;
    tableToInsertTo[position] -> occupied = true;

    size++;
}

void HashTable::insert(string key){

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now(); 

    if (size >capacity * LOAD_FACTOR){
        resize();
    }

    insertIntoTable(array, key);

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::milliseconds elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        
    totalElapsedTime += elapsedTime;
}

string HashTable::get(string key){
    string returnString = KEY + key + RIGHT_QUOTATION_MARK;

    size_t position = hash(key);
    size_t initialPosition = position;

    while (array[position] -> occupied){
        short compare = array[position] -> key.compare(key);
        if (compare == 0){
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

string HashTable::getTimeAs(string format){
    string returnString = BUILDING_TIME;
    if (TIME_FORMAT == MS)
    {
        int time = chrono::duration_cast<chrono::milliseconds>(totalElapsedTime).count();
        returnString = returnString  + MILLISECONDS + to_string(time) + MS + NEWLINE;

        return returnString;
    }
    if (TIME_FORMAT == NS)
    {
        int time = chrono::duration_cast<chrono::nanoseconds>(totalElapsedTime).count();
        returnString = returnString  + NANOSECONDS + to_string(time) + NS + NEWLINE;

        return returnString;
    }
    if (TIME_FORMAT == SEC)
    {
        int time = chrono::duration_cast<chrono::seconds>(totalElapsedTime).count();
        returnString = returnString  + SECONDS + to_string(time) + SEC + NEWLINE;

        return returnString;
    }
    return EMPTY;
}

