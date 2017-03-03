#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

// Test program
int main()
{
	BinarySearchTree<int> t;

	t.randomizedInsert(1);
	t.randomizedInsert(3);
	t.randomizedInsert(5);
	t.randomizedInsert(4);
	t.randomizedInsert(6);
	t.randomizedInsert(9);
	t.randomizedInsert(8);
	t.randomizedInsert(7);
		
	t.printTree();
	
	t.printLevel(6);
	cout << "get height" << endl;
	cout << t.getHeight() << endl;

	BinarySearchTree<int> t2;

	t2.insert(1);
	t2.insert(3);
	t2.insert(5);
	t2.insert(4);
	t2.insert(6);
	t2.insert(9);
	t2.insert(8);
	t2.insert(7);

	//t.printTree();

	t2.printLevel(6);

	cout << t2.getHeight() << endl;

	//cout << t.getChildCount() << endl;

	return 0;
}
