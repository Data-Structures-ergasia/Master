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
    while (temp != NULL)
    {
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
        cout << "Adding " << key << " on root " <<endl;
        root = newNode;
        return;
    }
    Node *tempRoot = NULL;
    Node *temp = root;
    short compare;

    while (temp != NULL)
    {
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
            //already exists
            temp->found++;
            return;
        }
    }

    compare = tempRoot->key.compare(key);

    switch (compare)
    {
    case 1:
        cout<<"Adding " << key << " left of " << tempRoot->key<< endl;
        tempRoot->left = newNode;
        break;
    case -1:
        cout<<"Adding " << key << " right of " << tempRoot->key << endl;

        tempRoot->right = newNode;
        break;
    default:
        tempRoot->found++;
    }
}

void BinaryTree::inorder()
{
    cout<<"Showing inorder traverse of bts :" <<endl;

    inorder(root);
}

void BinaryTree::inorder(Node *node)
{

    if (node == NULL)
    {
        return;
    }

    inorder(node->left);
    cout << node->key << "  was found " << node->found << " times" << endl;

    inorder(node->right);
}

void BinaryTree::preorder()
{
    cout<<"Showing preorder traverse of bts :" <<endl;

    preorder(root);
}

void BinaryTree::preorder(Node *node)
{
    if (node==NULL){
        return;
    }
    cout << node->key << "  was found " << node->found << " times" << endl;
    preorder(node->left);
    preorder(node->right);
}

void BinaryTree::postorder()
{
    cout<<"Showing postorder traverse of bts :" <<endl;
    postorder(root);
}

void BinaryTree::postorder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    postorder(node->left);
    postorder(node->right);
    cout << node->key << "  was found " << node->found << " times" << endl;
}

BinaryTree::~BinaryTree()
{
}
