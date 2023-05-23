#include "HashMap.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

int HashMap::hash(string key)
{
    char first = key[0];
    return (int)first - 97;
}

HashMap::HashMap()
{
    array = new (nothrow) Pair *[26];
    for (int i = 0; i < 26; i++)
    {
        array[i] = new Pair;
    }
}

bool HashMap::find(string key)
{
    int pos = hash(key);
    Pair *pair=array[pos];
    while(pair!=NULL){
        if (pair->key==key){
            pair->found++;
            return true;
        }
        pair=pair->next;
    }
    return false;
}

string HashMap::get(string key){
    int pos = hash(key);
    Pair *pair=array[pos];
    string returnString = "";
    while(pair!=NULL){
        if (pair->key==key){
            returnString = "Key :\"" + key + "\" was found " + to_string(pair->found) + " times!\n";
            return returnString;
        }
        pair=pair->next;
    }
    return "Key : " + key + " was not found!\n";
}

void HashMap::insert(string key)
{
    if(find(key)){
        return;
    }
    short pos = hash(key);
    if (array[pos]->key != "")
    {
        Pair *temp = array[pos];
        Pair *newPair = new Pair(key);

        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newPair;
    }
    else
    {
        array[pos] = new Pair(key);
    }

}


void HashMap::print()
{
    for (int i = 0; i < 26; i++)
    {
        if (array[i]->key != "")
        {

            Pair *pair = array[i];

            while (pair != NULL)
            {
                cout << "key : " << pair->key << " was found " << pair->found << " times."<< endl;
                pair = pair->next;
            }
        }
    }
}

HashMap::~HashMap()
{
    delete[] array;
}