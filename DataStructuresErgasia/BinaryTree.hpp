#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <string>
#include <stdlib.h>

#pragma once
using namespace std;

class Node
{
public:
	string key;
	int found;
	Node *left, *right;

	Node()
	{
		key = "";
		found = 1;
		left = NULL;
		right = NULL;
	}
	Node(string key)
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
	Node *root;
	void inorder(Node *node);
	void postorder(Node *node);
	void preorder(Node *node);
	
public:
	BinaryTree();
	void insert(string key);

	void find(string key);
	void inorder();
	void preorder();
	void postorder();
	void deleteKey(string key);
	~BinaryTree();
};
#endif