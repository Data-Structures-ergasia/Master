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

	void inorder(Node *node);
	void postorder(Node *node);
	void preorder(Node *node);
	void deleteBinaryTree(Node *node);
	
public:
	BinaryTree();
	void insert(std::string key);

	std::string find(std::string key);
    std::string getBuildingTime();

	void inorder();
	void preorder();
	void postorder();
	void deleteKey(std::string key);
	~BinaryTree();
};
#endif