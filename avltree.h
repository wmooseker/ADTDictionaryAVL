//avltree.h


#include "binarysearchtree.h"
#include "exception.h"
#include "treenode.h"
#include "item.h"

class AVLTree: public BinarySearchTree 
{
public:

AVLTree();

~AVLTree();

void addNewEntry(const Item& newItem) throw (Exception);

};

