#ifndef UNSORTEDARRAY_H
#define UNSORTEDARRAY_H
#pragma once
#include <stdlib.h>


using namespace std;

class UnsortedArray
{
private:
	struct entries
	{
		string key;
		unsigned int found;
	};

	entries *array;
	int size;
	int counter;

	void resize();

	int exists(string key);

public:
	UnsortedArray();
	void insert(string key);
	void print();
	void find(string key);
	void deleteKey(string key);
	~UnsortedArray();
};
#endif