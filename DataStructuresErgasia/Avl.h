#ifndef AVL_H
#define AVL_H
#include <string>
#include <stdlib.h>

#pragma once
using namespace std;

class AvlNode
{
public:
	string key;
	AvlNode *parent;
	int found,height;
	AvlNode *left, *right;

	AvlNode()
	{
		key = "";
		parent= NULL;
		found = 1;
		height=-2;
		left = NULL;
		right = NULL;
	}
	AvlNode(string key)
	{
		this->key = key;
		parent= NULL;
		found = 1;
		height=0;
		left = NULL;
		right=NULL;
	}
};

class Avl
{
private:
	AvlNode *root;
    std::chrono::nanoseconds totalElapsedTime;

	void calculateTime(chrono::steady_clock::time_point startTime);
	int compare(std::string s1, std::string s2);
public:
	Avl();
	void insert(string key);
	string find(string key);
    std::string getBuildingTime();
	~Avl();
};
#endif