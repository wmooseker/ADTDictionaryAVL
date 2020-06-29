// Implementation of ADT TreeNode

#include "treenode.h"

//creates a treenode object
//pre	treenode object does not exist
//post	treenode object is created and is empty
//usage TreeNode tNode
TreeNode::TreeNode()
{
   leftChild = nullptr;
   rightChild = nullptr;
   balance = 0;
}

//fills a empty treenode object
//pre treenode object exists and is empty
//post treenode object is given an item value and corresponding child pointers
//usage tNode = new TreeNode(item, leftChildPointer, rightChildPointer);
TreeNode::TreeNode(const Item& newItem, TreeNode* theLeft, TreeNode* theRight)
{
   item = newItem;
   leftChild = theLeft;
   rightChild = theRight;
   balance = 0;
}
