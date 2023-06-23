#include "Avl.h"
#include <iostream>
#include "Avl_Actions.cpp"
using namespace std;

Avl::Avl()
{
    chrono::steady_clock::time_point startTime = chrono::steady_clock::now(); 
    chrono::nanoseconds totalElapsedTime(0); 

    root = NULL;

    calculateTime(startTime);
}

string Avl::find(string key)
{
    int comparison;
    AvlNode *temp = root;
    string returnString = KEY + key + RIGHT_QUOTATION_MARK;

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

int Avl::compare(string s1, string s2){
    return s1.compare(s2);

}

void Avl::calculateTime(chrono::steady_clock::time_point startTime){
    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::nanoseconds elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
        
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
        calculateTime(startTime);
        return;
    }
    AvlNode *tempRoot = NULL;
    AvlNode *temp = root;
    AvlNode *flagtemp=NULL;

    int comparison;
    while (temp != NULL && !flag)
    {
        comparison = compare(temp->key, key);
        temp->height++;

        if (comparison > 0){
            //goLeft
            //checking if the tree below has a problem, if it does we flag the node we already are in order to fix the tree
            if(NodeTreeHeight(temp->left)+1>NodeTreeHeight(temp->right)+2){
                flagtemp=temp;
            }

            tempRoot = temp;
            temp = temp->left;
        } else if (comparison < 0){
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
            comparison = compare(temp->key, key);
            temp->height--;
            if (comparison > 0){
                //goLeft
                tempRoot = temp;
                temp = temp->left;
            } else if (comparison < 0){
                //goRight
                tempRoot = temp;
                temp = temp->right;
            } else {
                calculateTime(startTime);
                return;
            }
        }
    }
    //the parent of the new node is the tempRoot which is the previous node
    newNode->parent=tempRoot;
    comparison = compare(tempRoot->key, key);
    //we determine if the new node needs to go to the right or left child of tempRoot
    if (comparison > 0){
        tempRoot->left = newNode;
    } else if (comparison < 0 ){
        tempRoot->right = newNode;
    } else {
        tempRoot->found++;
    }

    //we check if the tree needs fixing
    if(flagtemp!=NULL && !flag){
        if(compare(flagtemp->key, key) > 0){
            //checking if we continue going left
            if(compare(flagtemp->left->key, key) > 0){
                Rotate(*flagtemp,false);
                
                calculateTime(startTime);

                return;
            }
            //we turned from left to right so we have an LR problem
            //first we make a left turn of the tree below our flagtemp
            Rotate(*flagtemp->left,true);
            //secong we make a right turn of the tree of flagtemp
            Rotate(*flagtemp,false);
        }else if(compare(flagtemp->key, key) < 0){
            //checking if we continue going right
            if(compare(flagtemp->right->key, key) < 0){
                Rotate(*flagtemp,true);
        
                calculateTime(startTime);

                return;
            }
            //we turned from left to right so we have an RL problem
            //first we make a right turn of the tree below our flagtemp
            Rotate(*flagtemp->right,false);
            //second we make a left turn of the tree of flagtemp
            Rotate(*flagtemp,true);
        }
    }
    
    calculateTime(startTime);
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
