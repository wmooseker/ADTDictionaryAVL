//file treenode.h
//author Dr. Y
//date October 8, 2018

//ADT TreeNode for a binary tree: data object a node with 
//                            an item and a pointer to left and right children
// operations: constructors
// Especially designed for the BinaryTree class

#ifndef TREENODE_H
#define TREENODE_H

#include <cstdlib>
#include "item.h"
using namespace std;

class TreeNode
{
public:
 
//creates a treenode object
//pre	treenode object does not exist
//post	treenode object is created and is empty
//usage TreeNode tNode
TreeNode();

//fills a empty treenode object
//pre treenode object exists and is empty
//post treenode object is given an item value and corresponding child pointers
//usage tNode = new TreeNode(item, leftChildPointer, rightChildPointer);
TreeNode(const Item& newItem, TreeNode* theLeft, TreeNode* theRight);
   
Item item;
TreeNode* leftChild;
TreeNode* rightChild;
int balance;
};
#endif


