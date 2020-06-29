//
// Specification of ADT Dictionary as ADT Binary Search Tree
//    Data object: A binary search tree T that is either empty or in the form
// 	       	   root
//           //    \
//	tree left       tree right
// where tree left and tree right are binary search trees. 
// data structure: a linked binary search tree
//     operations: create, destroy
//                 search the dictionary for an item given its text
//                 insert a new item into the dictionary
//                 remove an item from the dictionary given its text
//   associated operations: input and output
// filename binarysearchtree.cpp
// date: October 24, 2018


#include "binarysearchtree.h"

// recursive helper functions

//Releases memory for a binary tree
//pre: treep points to the root of a binary tree
//post: releases all of the nodes in the tree pointed to by treep
//    and leaves treep empty.
//usage: destroyBST (mroot);
void destroyBST(TreeNode*& treep)
{
	if ( treep != nullptr )
	{
		destroyBST ( treep -> leftChild );
		destroyBST ( treep -> rightChild );
		delete treep;
		treep = nullptr;
	}
}

// searches for smallest element in tree
// pre: treep is pointer to binary search tree
// post: anItem gets smallest element in subtree
// usage: searchSmallestHelper(treep -> rightChild, anItem);
bool searchSmallestHelper( TreeNode* treep, Item& anItem)
{
	
	if ( treep != nullptr )
	{
		bool isNull = searchSmallestHelper(treep->leftChild, anItem);
		
		if ( isNull )
			anItem = treep -> item;
		
		return false;
	} else
		return true;
		
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if BinarySearchTree object is not empty and 
//           targetText is found in Dictionary object
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object 
//       else throw an exception if not found or if empty
// usage: deleteHelper(targetText, root);
void deleteHelper(Key targetText, TreeNode*& treep)
{
	if (treep != nullptr)
	{
		if (targetText == treep -> item)
		{
			if ( treep -> rightChild == nullptr and treep -> leftChild == nullptr ) {
				delete treep;
				treep = nullptr;
			}
			else if ( treep -> rightChild != nullptr and treep -> leftChild == nullptr) {
				TreeNode* deletePtr = treep;
				treep = treep -> rightChild;
				
				deletePtr -> rightChild = nullptr;
				delete deletePtr;
				deletePtr = nullptr;
			} else if ( treep -> rightChild == nullptr and treep -> leftChild != nullptr) {
				TreeNode* deletePtr = treep;
				treep = treep -> leftChild;
				
				deletePtr -> leftChild = nullptr;
				delete deletePtr;
				deletePtr = nullptr;
			} else {
				Item minimumItem;
				
				searchSmallestHelper(treep -> rightChild, minimumItem);
				
				treep -> item = minimumItem;
				
				deleteHelper(minimumItem, treep -> rightChild);
			}
		} else if (targetText < treep -> item) {
			deleteHelper(targetText, treep -> leftChild);
		} else {
			deleteHelper(targetText, treep -> rightChild);
		}
	} else {
		throw Exception("That abbreviation was not found in the dictionary");
	}
}

// rebalances a binary tree
// pre: infile has items with keys in sorted order
// post: treep posts to a balanced BST containing items from infile
// usage: readTree(infile, root, numberOfEntries);
void readTree(istream& infile, TreeNode*& treep, int numberOfEntries) throw (Exception)
{
   if (numberOfEntries > 0)
   {
	  Item newItem;
      treep = new (nothrow) TreeNode(newItem, nullptr, nullptr);
	  
	  if ( treep == nullptr )
		  throw Exception("There was not enough memory to fully load tree, closing program.");
	  
      readTree(infile, treep -> leftChild, numberOfEntries / 2);
	  
      infile >> treep -> item;
	  
      readTree(infile, treep -> rightChild, (numberOfEntries - 1) / 2);
   }
}

// prints out the list in order
// pre: treep is assigned assigned a pointer to a root node of a binary search tree
// post: the tree is displayed on screen or saved to file depending on output
// usage: inorderHelper(output, root);
void inorderHelper(ostream& output, TreeNode* treep)
{	
	if (treep != nullptr)
	{
		inorderHelper(output, treep -> leftChild);
		output << treep -> item << endl;
		inorderHelper(output, treep -> rightChild);
	}
}

// searches a binary search tree for a certain text
// pre: treep is assigned a pointer to a root node of a binary search tree
//      targetText is assigned
// post: if targetText is found in the tree whose root node is treep
//          then the item in the root node is copied into anItem and
//          returns true; otherwise, returns false
// usage: isFound = searchHelper(root, targetText, anItem);
bool searchHelper(TreeNode* treep, const Key& targetText, Item& anItem)
{
   if (treep != nullptr)
   {
      if (targetText == treep -> item)
      {
         anItem = treep -> item;
         return true;
      } else if (targetText < treep -> item) {
         return searchHelper(treep -> leftChild, targetText, anItem);
      } else {
         return searchHelper(treep -> rightChild, targetText, anItem);
      }
   } else {
      return false;
   }
}

// recursive helper for addNewEntry
// pre: newItem has been assigned
// post: if there is room in the BinarySearchTree object and newItem's text
//            is not already there then newItem is appropriately added
//       else it throws an exception for either a full dictionary or
//            a message that it is already there
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void addHelper(TreeNode*& treep, const Item& newItem) throw (Exception)
{
	if (treep != nullptr)
	{
		if (newItem == treep -> item)
		{
			throw Exception("That abbreviation is already in the dictionary.");
		} else if ( newItem < treep -> item) {
			addHelper(treep -> leftChild, newItem);
		} else {
			addHelper(treep -> rightChild, newItem);
		}
	} else {
		treep = new (nothrow) TreeNode(newItem, nullptr, nullptr);
   } 
   
   if ( treep == nullptr )
	   throw Exception("There was not enough memory to add a new abbreviation.");
}

// displays dictionary onscreen or inputs
// 		into a file depending on output
// pre: output has been opened if it is a file
//      rightHandSideDictionary has been assigned items
// post: output contains each item on a separate line in the format
//		1
//		brb be right back
// usage: outfile << myDictionary;  
//
// Know it is not necessary, I just like the completeness it provides.  
ostream& operator<< (ostream& output, const BinarySearchTree& rightHandSideDictionary)
{
	//rightHandSideDictionary.inorderTraverse(output);
	return output;
}

// inputs items into a dictionary
// pre: input has been opened if it is a file
//      items are arranged in the following format
//      2
//      lol
//      laugh out loud
//      ttyl
//      talk to you later
// post: if there is room, 
//       all items in the input have been stored in rightHandSideDictionary
// usage: infile >> myDictionary;
istream& operator>> (istream& input, BinarySearchTree& rightHandSideDictionary) throw (Exception)
{
	char newline;
	Item newItem;
	
	// If tree already exists, destroy the tree to prevent memory leak
	if ( rightHandSideDictionary.root != nullptr )
	{
		//destroyBST( rightHandSideDictionary.root );
	}
		
	//input >> rightHandSideDictionary.numberOfItems;
	input.get(newline);
		
	//readTree(input, rightHandSideDictionary.root, rightHandSideDictionary.numberOfItems);

	return input;
}

// creates a new binary search tree
// post: BinarySearchTree object exists but is empty
// usage: BinarySearchTree myDictionary;	
BinarySearchTree::BinarySearchTree()
{
	numberOfItems = 0;
}

// destroys a binary search tree
// pre: BinarySearchTree object exists
// post: all memory for BinarySearchTree object has been freed
// usage: automatically done at the end of scope
BinarySearchTree::~BinarySearchTree()
{
	
}

// searchs for a meaning with a given text
// pre targetText has been assigned a value not already in the hash table
// post if an item with texting abbreviationthe same as targetText is found then
//          isFound is true and theItem is that item
//       else isFound is false
// usage  myDictionary.searchForMeaning(targetText, anItem, isFound);
void BinarySearchTree::searchForMeaning(const Key& targetText, Item& anItem, bool& isFound)
{
	isFound = searchHelper(root, targetText, anItem);
}

// inserts a new text' item into the dictionary
// pre: newItem has been assigned
// post: if there is room in the BinarySearchTree object and newItem's text
//            is not already there then newItem is appropriately added
//       else it throws an exception for either a full dictionary or
//            a message that it is already there
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void BinarySearchTree::addNewEntry(const Item& newItem) throw (Exception)
{
	addHelper(root, newItem);
	numberOfItems++;
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if BinarySearchTree object is not empty and 
//           targetText is found in Dictionary object
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object 
//       else throw an exception if not found or if empty
// usage: myDictionary.deleteEntry(targetText);
void BinarySearchTree::deleteEntry(const Key& targetText) throw (Exception)
{
	deleteHelper(targetText, root);
	numberOfItems--;
}

// prints out on screen or to file the BST in alphabetical order
// pre: tree exists
// post: prints out on screen or to file number of items followed by
//		the tree in alphabetical order, formatted 
//		2
//		afk away from keyboard
// 		brb be right back
//usage: tree.inorderTraverse(cout);  
// *****************************************************
void BinarySearchTree::inorderTraverse(ostream& output) const
{
	output << numberOfItems << endl;
	inorderHelper(output, root);
}
