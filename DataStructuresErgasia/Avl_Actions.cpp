#include "Avl.hpp"
#include <iostream>
using namespace std;
//we use this function in case the node we look for does not exist
int NodeTreeHeight(AvlNode* node)
{
    if (node == NULL)
        return -2;
 
    return node->height;
}

//if turn= true we turn left
//if turn= false we turn right
//for left turn we give the parent,height of the root to the right node and we give the left childs and height of the right child to the root 
//for right turn we give the parent,height of the root to the left node and we give the right childs and height of the left child to the root 
void Rotate(AvlNode &root,bool turn){
    AvlNode *tempParent=root.parent;
    //left turn of the tree
    if(turn){
        AvlNode *tempRoot=root.right->parent;
        root.parent=root.right;
        root.right->parent=tempParent;
        root.height=NodeTreeHeight(root.right->left) +1;
        if(root.right->left!=NULL){
            root.right->left->parent=tempRoot;
        }
        return;
    }
    //right turn of the tree
    AvlNode *tempRoot=root.left->parent;
    root.parent=root.left;
    root.left->parent=tempParent;
    root.height=NodeTreeHeight(root.left->right) +1;
    if(root.left->right!=NULL){
        root.left->right->parent=tempRoot;
    }
}
void deleteTree(AvlNode* &root){
    // Base case: empty tree
    if (root == nullptr) {
        return;
    }
 
    // delete left and right subtree first (Postorder)
    deleteTree(root->left);
    deleteTree(root->right);
 
    // delete the current node after deleting its left and right subtree
    delete root;
 
    // set root as null before returning
    root = nullptr;
}