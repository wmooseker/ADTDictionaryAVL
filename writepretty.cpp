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
		cout << "  " << text << endl;
		 if (treep -> leftChild != nullptr)
        {
            for (int i = 0; i <= level; i++)
                cout << '\t';
            cout << "\\" << endl;
			writePretty(treep -> leftChild, level);
		}
	}		
}