#include "BinaryTree.hpp"
#include <iostream>
using namespace std;

BinaryTree::BinaryTree()
{
    root = NULL;
}

void BinaryTree::find(string key)
{
     short compare;
    Node *temp = root;
    while (temp!=NULL){
         compare = temp->key.compare(key);

        switch (compare)
        {
        case 1:
            //goLeft
            temp = temp->left;
            break;
        case -1:
            //goRight
            temp = temp->right;
            break;
        default:
            cout << temp->key << " was found " << temp->found << " times. " << endl;
            return;
        }
    }
}

void BinaryTree::insert(string key)
{

    Node *newNode = new Node(key);

    if (root == NULL)
    {
        root = newNode;
        return;
    }
    Node *tempRoot = NULL;
    Node *temp = root;
    short compare;

    while (temp != NULL)
    {
       // cout << temp->key << endl;
        compare = temp->key.compare(key);

        switch (compare)
        {
        case 1:
            //goLeft
            tempRoot = temp;
            temp = temp->left;
            break;
        case -1:
            //goRight
            tempRoot = temp;
            temp = temp->right;
            break;
        default:
            temp->found++;
            return;
        }
    }

    compare = tempRoot->key.compare(key);

    switch (compare)
    {
    case 1:
        tempRoot->left = newNode;
        break;
    case -1:
        tempRoot->right = newNode;
        break;
    default:
        tempRoot->found++;
    }
}

void BinaryTree::inorder()
{
    inorder(root);
}

void BinaryTree::inorder(Node *node)
{

    if (node == NULL)
    {
        return;
    }

    inorder(node->left);
    cout << node->key << "  was found "<< node->found << " times" << endl;

    inorder(node->right);
}

void BinaryTree::print()
{
}

BinaryTree::~BinaryTree()
{
}

/*
 
    if (node == NULL)
    {
        return;
    }
    inorder(node->left);
    cout << node->key << endl;
    inorder(node->right); */