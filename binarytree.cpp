//file binarytree.cpp
//author Parker Mooseker and Carlos Vasquez Baur
//date 10/16/2018

//data object: a binary tree which is YOU DO
//data structure: a linked binary tree
//operations: YOU DO

#include "binarytree.h"
#include <iostream>
using namespace std;

// ***************** recursive helpers *****************
//Releases memory for a binary tree
//pre: treep points to the root of a binary tree
//post: releases all of the nodes in the tree pointed to by treep
//    and leaves treep empty.
//usage: destroyTree (mroot);

void destroyTree (TreeNode*& treep)
{
	if (treep != nullptr)
	{
		destroyTree(treep -> leftChild);
		destroyTree(treep -> rightChild);
		delete treep;
		treep = nullptr;
	}
}
//Copies one binary tree to another
//pre oldtreep points to the root of a binary tree
//post: newtreep points to the root of a binary tree
//  that has copies of the nodes of oldtreep's tree
//usage: copyTree (newptr, oldptr);
void copyTree (TreeNode*& newtreep, TreeNode* oldtreep) throw (Exception)
{
	if (newtreep != nullptr)
	{
		destroyTree(newtreep);
	}
	if (oldtreep == nullptr)
	{
		newtreep = nullptr;
	} 
	else 
	{
		newtreep = new (nothrow) TreeNode(oldtreep -> item, nullptr, nullptr);
		if (newtreep == nullptr)
		{
			throw Exception("no space in heap");
		}
		copyTree(newtreep->leftChild, oldtreep->leftChild);
		copyTree(newtreep->rightChild, oldtreep->rightChild);
	}
}


//prints the tree to look like a computer science tree
//pre: treep points to the root of a tree. level >= 0
//post: outputs the tree as in the example below
//
//  					  bar
//                  foo
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//nodes at the same level are indented the same.
//Viewer must rotate head 90 degrees in order to look like a cs tree
//usage: writePretty(root,0);
void writePretty (TreeNode* treep, int level)
{	
	if (treep != nullptr)
	{
		writePretty(treep -> rightChild, level += 1);
		if (treep -> rightChild != nullptr)
		{
			for (int j = 0;j <= level;j++)
				cout << '\t';
			cout << "/" << endl;
		}
		if (level == 1)
			cout << "root ->" ;
		else	
		{			
			for (int i = 0; i < level; i++)
				cout << '\t' ;
		}
		Key text = treep -> item;
		cout << "  " << text << ":" << treep->balance << endl;
		 if (treep -> leftChild != nullptr)
        {
            for (int i = 0; i <= level; i++)
                cout << '\t';
            cout << "\\" << endl;
			writePretty(treep -> leftChild, level);
		}
	}		
}


// ********** recursive helpers for the traversals ****************
//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the 
//     specified order. the items are separated by commas
//usage: preorder (mroot);   
//       similarly for the others
void preorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		cout << treep -> item << endl;
		preorder(treep -> leftChild);
		preorder(treep -> rightChild);
	}
}

void inorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		inorder(treep->leftChild);
		cout << treep->item << endl;
		inorder(treep->rightChild);
	}	
}


void postorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		postorder(treep->leftChild);
		postorder(treep->rightChild);
		cout << treep->item << endl;
	}
}

// **************************public methods************************


//creates an empty binary tree
//post: object is an empty binary tree
//usage: BinaryTree zags;
BinaryTree::BinaryTree()
{
   root = nullptr;
}

//creates a new binary tree that is a copy of an existing tree
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: BinaryTree zags (bulldog);
BinaryTree::BinaryTree(const BinaryTree& rightHandSideTree) throw (Exception)
{
   root = nullptr;
   copyTree(root, rightHandSideTree.root);
}

//releases the memory of a binary tree
//pre: object exists
//post: memory for the object has been released. object theoretically does not exist
//       but in practice, it is empty.
BinaryTree::~BinaryTree()
{
   destroyTree(root);
}

// ******************** member functions ********************************************
//@pre: binary tree object exists
// **********************************************************************************

//checks for an empty tree
//post: returns true if the object is empty; else returns false
//usage: if (tree.isEmpty())
bool BinaryTree::isEmpty() const
{
   return (root == nullptr);
}

//copies one tree to another
//pre: rightHandSideTree is an assigned tree.
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: atree = btree = ctree;
BinaryTree& BinaryTree::operator=(const BinaryTree& rightHandSideTree) throw (Exception)
{
	root = nullptr;
	copyTree(root, rightHandSideTree.root);
	return *this;
}

//prints the tree to look like a computer science tree
//post: outputs the tree as in the example below
//
//                        bar
//                  foo
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//nodes at the same level are indented the same.
//Viewer must rotate head 90 degrees in order to look like a cs tree
//usage: tree.prettyDisplay();
void BinaryTree::prettyDisplay()
{
	if (root == nullptr)
		cout << "The tree is empty" << endl;
	writePretty(root,0);
}

// *************** on the following traversals

//post: prints the objects in the tree in order specified
//usage: tree.preorderTraverse();  
//similarly for the other traversals
// *****************************************************
void BinaryTree::preorderTraverse ()
{
   preorder(root);
}
void BinaryTree::inorderTraverse (ostream& output) //change to incorporate output file
{
	inorder(root);
}
void BinaryTree::postorderTraverse()
{
	postorder(root);
}

//makes a full binary tree of height 3
//pre input is either cin or an open file
//    input's pointer is before the first item
//post: object is a full binary tree of height 3
//throws an exception if there is not enough room in the
//       heap to make the tree
//usage: bTree.makeFullTreeHeight3(input);
void BinaryTree::makeFullTreeHeight3(istream& input) throw (Exception)
{
   Item newguy;
   input >> newguy;
   root = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root == nullptr)	   // no memory from heap
		throw Exception("in BinaryTree: no memory from heap available for root item");
	input >> newguy;
	TreeNode *leftChildOne = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (leftChildOne == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	TreeNode *rightChildOne = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (rightChildOne == nullptr)
		throw Exception("no available memory in heap");
   input >> newguy;
   root -> leftChild = new (nothrow) TreeNode(newguy, leftChildOne, rightChildOne);
   if (root -> leftChild == nullptr)
		throw Exception("in BinaryTree: no memory from heap available for left child");
	input >> newguy;
	TreeNode *leftChildTwo = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (leftChildOne == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	TreeNode *rightChildTwo = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (rightChildOne == nullptr)
		throw Exception("no available memory in heap");
   input >> newguy;
   root->rightChild = new (nothrow) TreeNode(newguy, leftChildTwo, rightChildTwo);
   if (root->rightChild == nullptr)
       throw Exception("in BinaryTree: no room in the heap");
}

//makes a complete but not full binary tree of height 4 
//pre	input is either cin or an open file
//post	object is a complete tree of height 4
//throws an exception if there is not enough room in the
//       heap to make the tree
//usage: bTree.makeCompleteTreeHeight4(input);
void BinaryTree::makeCompleteTreeHeight4(istream& input) throw (Exception)
{
	Item newguy;
	
	input >> newguy;
	root = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (root == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	TreeNode *leftChildThree = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (leftChildThree == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	TreeNode *rightChildThree = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (rightChildThree == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	TreeNode *leftChildOne = new (nothrow) TreeNode(newguy, leftChildThree, rightChildThree);
	if (leftChildOne == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	TreeNode *leftChildFour = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (leftChildFour == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	TreeNode *rightChildOne = new (nothrow) TreeNode(newguy, leftChildFour, nullptr);
	if (rightChildOne == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	root -> leftChild = new (nothrow) TreeNode(newguy, leftChildOne, rightChildOne);
	if (root->leftChild == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	TreeNode *leftChildTwo = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (leftChildTwo == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	TreeNode *rightChildTwo = new (nothrow) TreeNode(newguy, nullptr, nullptr);
	if (rightChildTwo == nullptr)
		throw Exception("no available memory in heap");
	input >> newguy;
	root -> rightChild = new (nothrow) TreeNode(newguy, rightChildTwo, leftChildTwo);
	if (root->rightChild == nullptr)
	{
		throw Exception("no available memory in heap");
	}
	else
	{
		throw Exception("I am throwing an exception at you, Dr. Y. Do you have your catcher’s mitt ready?");
	}
}
