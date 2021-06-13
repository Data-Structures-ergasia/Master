#ifndef UNSORTEDARRAY_H
#define UNSORTEDARRAY_H
#pragma once
#include <stdlib.h>
#include <iostream>

using namespace std;

class UnsortedArray
{
private:
	struct entries
	{
		string key;
		int found;
	};

	entries *array;
	int size, counter;

	void resize();

	short exists(string key);

public:
	UnsortedArray();
	void add(string key);
	void print();
	void find(string key);
	~UnsortedArray();
};
#endif