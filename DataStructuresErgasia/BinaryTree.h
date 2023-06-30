#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <string>
#include <stdlib.h>

class Node
{
public:
	std::string key;
	int found;
	Node *left, *right;

	Node()
	{
		key = "";
		found = 1;
		left = NULL;
		right = NULL;
	}
	Node(std::string key)
	{
		this->key = key;
		found = 1;
		left = NULL;
		right=NULL;
	}
};

class BinaryTree
{
private:
    std::chrono::nanoseconds totalElapsedTime;

	Node *root;

	int compare(std::string s1, std::string s2);
	void calculateTime(chrono::steady_clock::time_point startTime);

	void deleteBinaryTree(Node *node);
	
public:
	BinaryTree();
	void insert(std::string key);

	std::string find(std::string key);
    std::string getBuildingTime();

	~BinaryTree();
};
#endif