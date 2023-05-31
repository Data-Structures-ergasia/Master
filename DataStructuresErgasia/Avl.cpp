#include "Avl.hpp"
#include <iostream>
#include "Avl_Actions.cpp"
using namespace std;

Avl::Avl()
{
    root = NULL;
}   

string Avl::find(string key)
{
    short compare;
    AvlNode *temp = root;
    string returnString;
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
            return "Key :\"" +key + "\" was found " + to_string(temp->found) + " times!\n";
        }
    }
    return "Key : " + key + " was not found!\n";
}
void Avl::insert(string key)
{
    bool flag=false;
    AvlNode *newNode = new AvlNode(key);
    //if the tree does not exist we create its root with the given key
    if (root == NULL)
    {
        root = newNode;
        return;
    }
    AvlNode *tempRoot = NULL;
    AvlNode *temp = root;
    AvlNode *flagtemp=NULL;
    short compare;
    while (temp != NULL && !flag)
    {
        compare = temp->key.compare(key);
        temp->height++;
        switch (compare)
        {
        //goLeft
        case 1:
            //checking if the tree below has a problem, if it does we flag the node we already are in order to fix the tree
            if(NodeTreeHeight(temp->left)+1>NodeTreeHeight(temp->right)+2){
            flagtemp=temp;
            }
            tempRoot = temp;
            temp = temp->left;
            break;
        //goRight
        case -1:
            //checking if the tree below has a problem, if it does we flag the node we already are in order to fix the tree
            if( NodeTreeHeight(temp->right)+1>NodeTreeHeight(temp->left)+2){
                flagtemp=temp;
            }
            tempRoot = temp;
            temp = temp->right;
            break;
        //the given key exists, so the extra heights we have added are false so we alert the problem with a flag
        default:
            flag=true;
            temp->found++;
        }
    }
    //if it already existed we remove the height falsely given
    //in its loop we remove the height we have given to each node
    if(flag){
        tempRoot = NULL;
        temp=root;
        while (temp != NULL)
        {
            compare = temp->key.compare(key);
            temp->height--;
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
                return;
            }
        }
    }
    //the parent of the new node is the tempRoot which is the previous node
    newNode->parent=tempRoot;
    compare = tempRoot->key.compare(key);
    //we determine if the new node needs to go to the right or left child of tempRoot
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
    //we check if the tree needs fixing
    //cout<<flagtemp->key<<endl;
    if(flagtemp!=NULL && !flag){
        if(flagtemp->key.compare(key)==1){
            //checking if we continue going left
            if(flagtemp->left->key.compare(key)==1){
                RotateOneWay(*flagtemp,false);
                return;
            }
            //we turned from left to right so we have an LR problem
            //first we make a left turn of the tree below our flagtemp
            RotateOneWay(*flagtemp->left,true);
            //secong we make a right turn of the tree of flagtemp
            RotateOneWay(*flagtemp,false);
        }else if(flagtemp->key.compare(key)==-1){
            //checking if we continue going right
            if(flagtemp->right->key.compare(key)==-1){
                RotateOneWay(*flagtemp,true);
                return;
            }
            //we turned from left to right so we have an RL problem
            //first we make a right turn of the tree below our flagtemp
            RotateOneWay(*flagtemp->right,false);
            //secong we make a left turn of the tree of flagtemp
            RotateOneWay(*flagtemp,true);
        }
    }
}
Avl::~Avl()
{
}