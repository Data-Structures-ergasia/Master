#include "BinaryTree.h"
#include "Constants.h"
#include <iostream>
#include <chrono>
#include <string>

using namespace constants;
using namespace std;
// constructor, adding time passed to be more complete
BinaryTree::BinaryTree()
{
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now(); 
    chrono::nanoseconds totalElapsedTime(0); 

    root = NULL;

    calculateTime(startTime);
}

int BinaryTree::compare(string s1, string s2){
    return s1.compare(s2);
}

void BinaryTree::calculateTime(chrono::steady_clock::time_point startTime){
    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::nanoseconds elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
        
    totalElapsedTime += elapsedTime;
}

// return the time it took for building the structure, i.e. inserting the keys
string BinaryTree::getBuildingTime(){
    string returnString = BUILDING_TIME;

    if (BINARY_TREE_BUILD_TIME_UNIT == MS)
    {
        int time = chrono::duration_cast<chrono::milliseconds>(totalElapsedTime).count();
        returnString = returnString  + MILLISECONDS + to_string(time) + MS + NEWLINE;

        return returnString;
    }

    if (BINARY_TREE_BUILD_TIME_UNIT == NS)
    {
        int time = chrono::duration_cast<chrono::nanoseconds>(totalElapsedTime).count();
        returnString = returnString  + NANOSECONDS + to_string(time) + NS + NEWLINE;

        return returnString;
    }

    if (BINARY_TREE_BUILD_TIME_UNIT == SEC)
    {
        int time = chrono::duration_cast<chrono::seconds>(totalElapsedTime).count();
        returnString = returnString  + SECONDS + to_string(time) + SEC + NEWLINE;

        return returnString;
    }
    return EMPTY;
}

// find the key in question, returns a string that is printed to the output file
string BinaryTree::find(string key)
{
    string returnString = KEY + key + RIGHT_QUOTATION_MARK;
    int comparison;
    Node *temp = root;
    while (temp != NULL)
    {
        comparison = compare(temp->key, key);

        if (comparison > 0){
            //goLeft
            temp = temp->left;
        } else if (comparison < 0){
            //goRight
            temp = temp->right;
        } else {
            returnString += WAS_FOUND + to_string(temp -> found) + TIMES + NEWLINE;
            return returnString;
        }
        
    }

    return returnString + WAS_NOT_FOUND + NEWLINE;
}

// insert the key, if it exists increase its found field by one
void BinaryTree::insert(string key)
{
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now(); 

    Node *newNode = new Node(key);

    if (root == NULL)
    {
        root = newNode;
        return;
    }
    Node *tempRoot = NULL;
    Node *temp = root;
    int comparison;

//search if the key exists
    while (temp != NULL)
    {
        comparison = compare(temp->key, key);

        if (comparison > 0 ){
            //goLeft
            tempRoot = temp;
            temp = temp->left;
        } else if (comparison < 0){
            //goRight
            tempRoot = temp;
            temp = temp->right;
        } else {
            //key was found
            temp->found++;

            calculateTime(startTime);
            return;
        }
    }

    comparison = compare(tempRoot->key, key);
    
    // insert the new node to the correct "side"
    if (comparison > 0){
        tempRoot->left = newNode;
    } else if (comparison < 0 ){
        tempRoot->right = newNode;
    } else {
        tempRoot->found++;
    }

    calculateTime(startTime);
}

// print the inorder of binary tree to the console
void BinaryTree::inorder()
{
    cout<< IN_ORDER << NEWLINE;

    inorder(root);
}

void BinaryTree::inorder(Node *node)
{

    if (node == NULL)
    {
        return;
    }

    inorder(node->left);
    cout << KEY << node->key << RIGHT_QUOTATION_MARK << WAS_FOUND << node->found << TIMES << NEWLINE;

    inorder(node->right);
}

// print the preorder of the binary tree to the console
void BinaryTree::preorder()
{
    cout<< PRE_ORDER <<endl;

    preorder(root);
}

void BinaryTree::preorder(Node *node)
{
    if (node==NULL){
        return;
    }
    
    cout << KEY << node->key << RIGHT_QUOTATION_MARK << WAS_FOUND << node->found << TIMES << NEWLINE;

    preorder(node->left);
    preorder(node->right);
}

//print the postorder of binary  tree to the console
void BinaryTree::postorder()
{
    cout<< POST_ORDER <<endl;
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
    
    cout << KEY << node->key << RIGHT_QUOTATION_MARK << WAS_FOUND << node->found << TIMES << NEWLINE;
}

//delete the tree and free its space
void BinaryTree::deleteBinaryTree(Node* node){
    // if the tree is empty there is nothing to delete
    if (node == NULL) {
        return;
    }
 
    // delete left and right subtree
    deleteBinaryTree(node->left);
    deleteBinaryTree(node->right);
    // delete the current node
    delete node;
    // set root as null to alert deletion
    node = NULL;
}

BinaryTree::~BinaryTree()
{
    Node* del=root;
    deleteBinaryTree(del);
}
