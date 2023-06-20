#include "Avl.h"
#include <iostream>
#include "Avl_Actions.cpp"
using namespace std;

Avl::Avl()
{
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now(); 
    chrono::milliseconds totalElapsedTime(0); 

    root = NULL;

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::milliseconds elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        
    totalElapsedTime += elapsedTime;
}

string Avl::find(string key)
{
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
    short compare;
    AvlNode *temp = root;
    string returnString;
    while (temp != NULL)
    {
        compare = temp->key.compare(key);

        if (compare > 0){
            //goLeft
            temp = temp->left;
        } else if (compare < 0){
            //goRight
            temp = temp->right;
        } else {
            return "Key : \"" +key + "\" was found " + to_string(temp->found) + " times!\n";
        }
    }
    return "Key : " + key + " was not found!\n";
    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::milliseconds elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        
    totalElapsedTime += elapsedTime;
}
void Avl::insert(string key)
{
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now(); 
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

        if (compare > 0){
            //goLeft
            //checking if the tree below has a problem, if it does we flag the node we already are in order to fix the tree
            if(NodeTreeHeight(temp->left)+1>NodeTreeHeight(temp->right)+2){
                flagtemp=temp;
            }

            tempRoot = temp;
            temp = temp->left;
        } else if (compare < 0){
        //goRight
        //checking if the tree below has a problem, if it does we flag the node we already are in order to fix the tree
            if( NodeTreeHeight(temp->right)+1>NodeTreeHeight(temp->left)+2){
                    flagtemp=temp;
            }
            tempRoot = temp;
            temp = temp->right;
        } else {
            //the given key exists, so the extra heights we have added are false so we alert the problem with a flag
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
            if (compare > 0){
                //goLeft
                tempRoot = temp;
                temp = temp->left;
            } else if (compare < 0){
                //goRight
                tempRoot = temp;
                temp = temp->right;
            } else {
                return;
            }
        }
    }
    //the parent of the new node is the tempRoot which is the previous node
    newNode->parent=tempRoot;
    compare = tempRoot->key.compare(key);
    //we determine if the new node needs to go to the right or left child of tempRoot
    if (compare > 0){
        tempRoot->left = newNode;
    } else if (compare < 0 ){
        tempRoot->right = newNode;
    } else {
        tempRoot->found++;
    }

    //we check if the tree needs fixing
    if(flagtemp!=NULL && !flag){
        if(flagtemp->key.compare(key) > 0){
            //checking if we continue going left
            if(flagtemp->left->key.compare(key) > 0){
                Rotate(*flagtemp,false);
                return;
            }
            //we turned from left to right so we have an LR problem
            //first we make a left turn of the tree below our flagtemp
            Rotate(*flagtemp->left,true);
            //secong we make a right turn of the tree of flagtemp
            Rotate(*flagtemp,false);
        }else if(flagtemp->key.compare(key) < 0){
            //checking if we continue going right
            if(flagtemp->right->key.compare(key) < 0){
                Rotate(*flagtemp,true);
                return;
            }
            //we turned from left to right so we have an RL problem
            //first we make a right turn of the tree below our flagtemp
            Rotate(*flagtemp->right,false);
            //second we make a left turn of the tree of flagtemp
            Rotate(*flagtemp,true);
        }
    }
    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::milliseconds elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        
    totalElapsedTime += elapsedTime;
}
string Avl::getBuildingTime(){
    string returnString = BUILDING_TIME;

    if (AVL_TREE_BUILD_TIME_UNIT == MS)
    {
        int time = chrono::duration_cast<chrono::milliseconds>(totalElapsedTime).count();
        returnString = returnString  + MILLISECONDS + to_string(time) + MS + NEWLINE;

        return returnString;
    }

    if (AVL_TREE_BUILD_TIME_UNIT == NS)
    {
        int time = chrono::duration_cast<chrono::nanoseconds>(totalElapsedTime).count();
        returnString = returnString  + NANOSECONDS + to_string(time) + NS + NEWLINE;

        return returnString;
    }

    if (AVL_TREE_BUILD_TIME_UNIT == SEC)
    {
        int time = chrono::duration_cast<chrono::seconds>(totalElapsedTime).count();
        returnString = returnString  + SECONDS + to_string(time) + SEC + NEWLINE;

        return returnString;
    }
    return EMPTY;
}
//deleting the Avl tree
Avl::~Avl()
{
    AvlNode* del=root;
    deleteTree(del);
}
