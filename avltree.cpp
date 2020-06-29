// avltree.cpp

#include "avltree.h"
const int MAXHEIGHT = 15;
struct SearchPath
{
    TreeNode* path[MAXHEIGHT];
    int size;
    int pivotIndex;
    SearchPath();   
};
SearchPath::SearchPath()
{
    size = 0;
    pivotIndex = -1;
    for(int i = 0; i < MAXHEIGHT; i++) 
	{
		path[i] = nullptr;
	}
}

AVLTree::AVLTree()
{
}

AVLTree::~AVLTree()
{
}


// Helper function that adds new entry to the search tree
//		and creates a search path from root to new entry
// Pre: treeptr points an AVL tree, search is empty SearchPath
//		with size zero and newItem exists. 
// Post: newItem is added to the tree and 
//		search is a search path from root to new entry
//		with appropriate size
//		If newItem is already in the search tree or
//		there was no memory for new TreeNode exception
//		is thrown.
// Usage: addNewEntryAndMakeSearchPath(newItem, root, search);
void addnewEntryAndMakeSearchPath(const Item& newItem, TreeNode*& treeptr, SearchPath& search) throw (Exception)
{
	if (treeptr != nullptr)
	{
		search.path[search.size] = treeptr;
		search.size += 1;
		
		if (newItem == treeptr -> item)
		{
			throw Exception("That abbreviation is already in the dictionary.");
		} else if ( newItem < treeptr -> item) {
			addnewEntryAndMakeSearchPath(newItem, treeptr -> leftChild, search);
		} else {
			addnewEntryAndMakeSearchPath(newItem, treeptr -> rightChild, search);
		}
	} else {
		treeptr = new (nothrow) TreeNode(newItem, nullptr, nullptr);
		search.path[search.size] = treeptr;
		search.size += 1;
	} 
   
   if ( treeptr == nullptr )
	   throw Exception("There was not enough memory to add a new abbreviation.");
}



// Detects whether the AVLTree has a pivot and assigns pivotIndex to 
//		the location of the node containing the pivot
// Pre: SearchPath has been declared, AVLTree exists
// Post: If there is a pivot, pivot index is assigned in search 
// 			to the location of the node containing the pivot and we return false, 
//			else return true
// usage: bool pivot = hasNoPivot(search);
bool hasNoPivot(SearchPath& search)
{
   int index = search.size - 1;
   while(index >= 0)
   {
      if(search.path[index] -> balance != 0)
	  {
		 search.pivotIndex = index;
	     return false;
	  }
	  index--;		
   }
   return true;
}


//Description: Rebalance the tree from start index down
//pre: Unbalanced searchPath is passed along with the pivot index.
//post: AVL Tree that was passed has correct index balances
//usage: fixBalances(search, pivotIndex);

void fixBalances(const SearchPath& search, int start){
	for(int i = start; i < search.size - 1; i++){
		if(search.path[i]->rightChild == search.path[i+1]){
			search.path[i]->balance++;
		} else{
			search.path[i]->balance--;
		}
	}
}


// tells whether the new item has been added to the short or tall side
// pre: SearchPath object exists
// post: returns true if added to the short side, false if added to the tall side
// usage: if(isAddedToShortSide(search))
bool isAddedToShortSide(const SearchPath& search)
{
	return ((search.path[search.pivotIndex] -> balance == -1 && search.path[search.pivotIndex + 1] == search.path[search.pivotIndex] -> rightChild)
	      ||(search.path[search.pivotIndex] -> balance ==  1 && search.path[search.pivotIndex + 1] == search.path[search.pivotIndex] -> leftChild));
}


//Tests whether or not the AVL tree needs a right rotation.
//Pre: Search exists/ is initialized
//Post: Returns true if a right rotation is needed in the AVL tree.
//Usage: isSingleRotateRight(mySearchPath);
bool isSingleRotateRight(const SearchPath& search)
{
	return ((search.path[search.pivotIndex + 1] == search.path[search.pivotIndex] -> leftChild) &&
				(search.path[search.pivotIndex + 2] == search.path[search.pivotIndex + 1] -> leftChild));
}

//	This function starts at the pivot and returns true if the search.path is the right right case
//  	and decides whether it needs a single left rotation
//	Pre: the AVL tree is populated with items and pivot index is assigned in the tree
//	Post: the function returns true if the search path goes right twice in a row
//		  and returns false otherwise
//	usage: isSingleRotateLeft(search);
bool isSingleRotateLeft(const SearchPath& search)
{
	if ((search.path[search.pivotIndex]->rightChild == search.path[search.pivotIndex + 1]) && (search.path[search.pivotIndex]->rightChild->rightChild == search.path[search.pivotIndex + 2]))
		return true;
	else
		return false;
}


// goes to the pivot and checks to see if the avl tree goes left then right 
// pre: SearchPath exists
// post: returns true if search path goes left then right and false otherwise
// usage: isDoubleRotateLeftRight(SearchPath& mySearchPath);
bool isDoubleRotateLeftRight(const SearchPath& search)
{
	if (search.path[search.pivotIndex] -> leftChild == search.path[search.pivotIndex + 1])
	{
		if(search.path[search.pivotIndex + 1] -> rightChild == search.path[search.pivotIndex + 2])
			return true;
	}
	return false;
}

//performs a single left rotation given a search path
//pre	search path and AVLTree exists
//post	
TreeNode* doSingleRotateLeft(SearchPath& search)
{
	TreeNode* cloud = search.path[search.pivotIndex - 1];
	TreeNode* pivot = search.path[search.pivotIndex];
	TreeNode* pivotChild = search.path[search.pivotIndex + 1];
	TreeNode* treeOne = pivot->leftChild;
	TreeNode* treeTwo = pivotChild->leftChild;
	TreeNode* treeThree = pivotChild->rightChild;
	pivotChild->rightChild = treeThree;
	pivotChild->leftChild = pivot;
	pivot->leftChild = treeOne;
	pivot->rightChild = treeTwo;
	
	if (search.pivotIndex == 0)
	{
		search.path[0] = pivotChild;
	}
	else if (cloud->rightChild == pivot)
	{
		cloud->rightChild = pivotChild;
	}
	else 
	{
		cloud->leftChild = pivotChild;
	}
	pivotChild->balance = 0;
	pivot->balance = 0;
	return search.path[0];
}

TreeNode* doSingleRotateRight(SearchPath& search)
{
	TreeNode* cloud = search.path[search.pivotIndex - 1];
    TreeNode* pivot = search.path[search.pivotIndex];
    TreeNode* pivotChild = search.path[search.pivotIndex + 1];
    TreeNode* treeOne = pivot->rightChild;
    TreeNode* treeTwo = pivotChild->rightChild;
    TreeNode* treeThree = pivotChild->leftChild;
	pivotChild->leftChild = treeThree;
    pivotChild->rightChild = pivot;
    pivot->rightChild = treeOne;
    pivot->leftChild = treeTwo;

    if (search.pivotIndex == 0)
    {
        search.path[0] = pivotChild;
    }
    else if (cloud->rightChild == pivot)
    {
        cloud->rightChild = pivotChild;
    }
    else
    {
        cloud->leftChild = pivotChild;
    }
	pivotChild->balance = 0;
    pivot->balance = 0;
	return search.path[0];
}

TreeNode* doDoubleRotateLeftRight(SearchPath &search)
{
    TreeNode* cloud = search.path[search.pivotIndex - 1];
    TreeNode* pivot = search.path[search.pivotIndex];
	TreeNode* pivotChild = search.path[search.pivotIndex + 1];
    TreeNode* grandChild = search.path[search.pivotIndex + 2];
    TreeNode* treeOne = pivotChild->leftChild;
    TreeNode* treeTwo = grandChild->leftChild;
    TreeNode* treeThree = grandChild->rightChild;
    TreeNode* treeFour = pivot->rightChild;
	bool leftChild = search.path[search.size - 2]->leftChild == search.path[search.size - 1];
	grandChild->leftChild = pivotChild;
    grandChild->rightChild = pivot;
    pivotChild->leftChild = treeOne;
    pivotChild->rightChild = treeTwo;
    pivot->leftChild = treeThree;
    pivot->rightChild = treeFour;
    grandChild->balance = 0;
	if (search.pivotIndex == 0)
    {
        search.path[0] = grandChild;
    }
    else if (cloud->rightChild == pivot)
    {
        cloud->rightChild = grandChild;
    }
    else
    {
        cloud->leftChild = grandChild;
    }
	if (leftChild)
    {
        pivot->balance = 1;
        pivotChild->balance = 0;
    }
    else
    {
        pivot->balance = 0;
        pivotChild->balance = 1;
    }
    search.path[search.size - 2]->balance = 0;
	return search.path[0];
}

TreeNode *doDoubleRotateRightLeft(SearchPath &search)
{
    TreeNode *cloud = search.path[search.pivotIndex - 1];
    TreeNode *pivot = search.path[search.pivotIndex];
    TreeNode *pivotChild = search.path[search.pivotIndex + 1];
    TreeNode *grandChild = search.path[search.pivotIndex + 2];
    TreeNode *T1 = pivotChild->rightChild;
    TreeNode *T2 = grandChild->rightChild;
    TreeNode *T3 = grandChild->leftChild;
    TreeNode *T4 = pivot->leftChild;

    bool leftChild = search.path[search.size - 2]->leftChild == search.path[search.size - 1];

    grandChild->rightChild = pivotChild;
    grandChild->leftChild = pivot;
    pivotChild->rightChild = T1;
    pivotChild->leftChild = T2;
    pivot->rightChild = T3;
    pivot->leftChild = T4;
    grandChild->balance = 0;

    if (search.pivotIndex == 0)
    {
        search.path[0] = grandChild;
    }
    else if (cloud->rightChild == pivot)
    {
        cloud->rightChild = grandChild;
    }
    else
    {
        cloud->leftChild = grandChild;
    }

    if (leftChild)
    {
        pivot->balance = 0;
        pivotChild->balance = 1;
    }
    else
    {
        pivot->balance = 1;
        pivotChild->balance = 0;
    }
    search.path[search.size - 2]->balance = 0;

    return search.path[0];
}

void AVLTree::addNewEntry(const Item& newItem) throw (Exception)
{
   SearchPath search;
   addnewEntryAndMakeSearchPath(newItem, root, search);
   
   if(hasNoPivot(search))
   {
	  fixBalances(search, 0);
   }
   else if (isAddedToShortSide(search))
   {
      fixBalances(search, search.pivotIndex);
   }
   else if (isSingleRotateLeft(search))
   {
	   root = doSingleRotateLeft(search);
	   fixBalances(search, search.pivotIndex+2);
   }
   else if (isSingleRotateRight(search))
   {
		root = doSingleRotateRight(search);
		fixBalances(search, search.pivotIndex+2);
   }
   else if (isDoubleRotateLeftRight(search))
   {
	   root = doDoubleRotateLeftRight(search);
	   fixBalances(search, search.pivotIndex+3);
   }
   else
   {
	   root = doDoubleRotateRightLeft(search);
	   fixBalances(search, search.pivotIndex+3);
   }
}

