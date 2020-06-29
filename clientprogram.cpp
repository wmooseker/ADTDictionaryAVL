//clientprogram.cpp

#include "avltree.h"
#include "exception.h"
#include <fstream>
#include "binarytree.h"
using namespace std;

void openInputFile(ifstream& inputFile)
{
	inputFile.open("in.dat");
	if (inputFile.fail())
	{
		cout << "failed to open file";
		exit(1);
	}
}

void readIntoTree(istream& input, AVLTree& tree)
{
	Item newItem;
	int numItems;
	input >> numItems;
	//input.get();
	for(int i = 0; i < numItems; i++)
	{
		input >> newItem;
		tree.addNewEntry(newItem);
	}
}

void runSubcaseTest(string subcaseName, istream& input)
{
	AVLTree testTree;
	Item newItem;
	cout << subcaseName << endl;
	readIntoTree(input, testTree);
	testTree.prettyDisplay();
	input >> newItem;
	try 
	{
		cout << "adding : " << newItem << endl;
		cout << endl;
		testTree.addNewEntry(newItem);
	}
	catch (Exception anException)
	{
		throw Exception(" exception ");
	}
	testTree.prettyDisplay();
	cout << endl;
}

int main ()
{
	ifstream input;
	openInputFile(input);
	cout << "		HAS NO PIVOT" << endl;
	runSubcaseTest("Test 1: CASE OF EMPTY TREE", input);
	runSubcaseTest("Test 2: CASE OF HEIGHT 1", input);
	runSubcaseTest("Test 3: CASE OF HEIGHT 2", input);
	cout << "		ADDED TO SHORT SIDE" << endl;
	runSubcaseTest("Test 1: CASE OF ADDING TO RIGHT", input);
	runSubcaseTest("Test 2: CASE OF ADDING TO LEFT", input);
	cout << "		SINGLE ROTATE LEFT" << endl;
	runSubcaseTest("Test 1: PIVOT INDEX AT 0", input);
    runSubcaseTest("Test2: CLOUD POINTING TO RIGHT CHILD", input);
    runSubcaseTest("Test3: CLOUD POINTING TO LEFT CHILD", input);
	cout << "       SINGLE ROTATE LEFT" << endl;
    runSubcaseTest("Test1: PIVOT INDEX AT 0", input);
    runSubcaseTest("Test2: CLOUD POINTING TO RIGHT CHILD", input);
    runSubcaseTest("Test3: CLOUD POINTING TO LEFT CHILD", input);
	cout << "       DOUBLE ROTATE LEFT RIGHT" << endl;
    runSubcaseTest("Test1: PIVOT INDEX AT 0", input);
    runSubcaseTest("Test2: NEW ITEM AT LEFT CHILD", input);
    runSubcaseTest("Test3: NEW ITEM AT RIGHT CHILD", input);
    runSubcaseTest("Test4: CLOUD POINTING TO LEFT CHILD", input);
    runSubcaseTest("Test5: CLOUD POINTING TO RIGHT CHILD", input);
	cout << "       DOUBLE ROTATE RIGHT LEFT" << endl;
    runSubcaseTest("Test1: PIVOT INDEX AT 0", input);
    runSubcaseTest("Test2: NEW ITEM AT RIGHT CHILD", input);
    runSubcaseTest("Test3: NEW ITEM AT LEFT CHILD", input);
    runSubcaseTest("Test4: CLOUD POINTING TO RIGHT CHILD", input);
    runSubcaseTest("Test5: CLOUD POINTING TO LEFT CHILD", input);
	input.close();
    return 0;
}
