#ifndef HASHMAP_H
#define HASHMAP_H
#pragma once
#include <stdlib.h>

class Pair
{
public:
	string key;
	int found;
	Pair *next;

	Pair()
	{
		key = "";
		found = 1;
		next = nullptr;
	}
	Pair(string key)
	{
		this->key = key;
		found = 1;
		next = nullptr;
	}


};

class HashMap
{

private:
	Pair **array;

	short hash(string key);
	bool find(string key);

public:
	HashMap();
	
	void insert(string key);
	void print();
	void get(string key);
	~HashMap();
};
#endif