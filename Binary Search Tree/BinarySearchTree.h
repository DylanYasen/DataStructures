#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree() :root(NULL)
	{
		srand(123456789);
	}

	BinarySearchTree(const BinarySearchTree & rhs) : root(NULL)
	{
		*this = rhs;
	}

	/**
	 * Destructor for the tree
	 */
	~BinarySearchTree()
	{
		makeEmpty();
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMin() const
	{
		if (isEmpty())
			throw UnderflowException();
		return findMin(root)->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMax() const
	{
		if (isEmpty())
			throw UnderflowException();
		return findMax(root)->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains(const Comparable & x) const
	{
		return contains(x, root);
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 */
	bool isEmpty() const
	{
		return root == NULL;
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printTree(ostream & out = cout) const
	{
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			printTree(root, out);
	}

	void printLevel(int level){

		int height = getHeight();

		for (int i = 0; i <= level; i++){

			if (i > height)
				return;

			cout << "Level " << i << ": ";
			printLevel(root, i);
			cout << endl;
		}
	}

	int getHeight(){
		return (getHeight(root) - 1);
	}

	/**
	 * Make the tree logically empty.
	 */
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert(const Comparable & x) { insert(x, root); }


	/*

	*/
	void randomizedInsert(const Comparable & x){

		randomizedInsert(x, root);
	}

	const int nextInt(int size){

		return rand() % size + 1;
	}

	unsigned int getChildCount() {

		unsigned int size = 0;

		countChild(root, size);

		return size;
	}


	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove(const Comparable & x)
	{
		remove(x, root);
	}

	/**
	 * Deep copy.
	 */
	const BinarySearchTree & operator=(const BinarySearchTree & rhs)
	{
		if (this != &rhs)
		{
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	}




private:  // this private BinaryNode is within BST
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		unsigned int size;

		BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
			: element(theElement), left(lt), right(rt), size(1) {
		}
	};

	BinaryNode *root;

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(const Comparable & x, BinaryNode * & t)
	{
		if (t == NULL) { t = new BinaryNode(x, NULL, NULL); } // no node present yet
		else if (x < t->element) { insert(x, t->left); } // value in CURRENT root 't' < new value
		else if (t->element < x) { insert(x, t->right); }
		else;  // Duplicate; do nothing

	}

	void randomizedInsert(const Comparable & x, BinaryNode * & t){

		// insert new node
		if (t == NULL) {
			t = new BinaryNode(x, NULL, NULL);

			cout << "created new node: " << x << endl;

			// set to root if no root
			if (root == NULL) this->root = t;

			nextInt(1);
		}

		else
		{
			// temp root
			BinaryNode* parent = root;
			parent = getParent(parent, t);

			//// randomization
			//int s;
			//if (t == NULL)
			//	s = 1;
			//else
			//	s = parent->size;

			//int randInt = nextInt(s);

			int s = getChildCount(t) + 1;
			int randInt = nextInt(s);

			cout << "get random interger: " << randInt << ".  grand parent's size: " << getChildCount(parent) + 1 << endl;

			// if randInt == size
			if (randInt == getChildCount(parent) + 1){
				insertAtRoot(x, root);
			}

			// keep going
			else{
				if (x < t->element) { t->size++; randomizedInsert(x, t->left); }
				else if (t->element < x){ t->size++; randomizedInsert(x, t->right); }
			}
		}
	}

	BinaryNode* getParent(BinaryNode* rt, BinaryNode* node){

		if (node == rt)
			return node;

		if (node->left == NULL && node->right == NULL)
			return node;

		while (rt->left != node && rt->right != node){

			if (node->element < rt->element)
				rt = rt->left;
			else
				rt = rt->right;
		}

		return rt;
	}

	void insertAtRoot(const Comparable & x, BinaryNode * & t){

		// insert new node
		if (t == NULL){
			t = new BinaryNode(x, NULL, NULL);

			cout << "created new node at root: " << x << endl;

			// 
			rotateToRoot(t);
		}

		// insert new node as leaf
		//insert(x, t);

		else if (t->element < x){
			insertAtRoot(x, t->right);
		}
		else{
			insertAtRoot(x, t->left);
		}
	}

	void rotateRight(BinaryNode * & rt){

		if (rt->left == NULL)return;

		// keep left child
		BinaryNode* newRoot = clone(rt->left);
		newRoot->size = rt->size;

		// old root is new root's right chil
		newRoot->right = rt;

		int tempSize = rt->size;

		// newRoot has one more child -> old root
		newRoot->size = rt->size;
		// += old root size

		// oldRoot lost one child -> new root
		rt->size -= tempSize;
		// -= new root size

		// set new root
		this->root = newRoot;

		cout << "rotate right" << endl;
	}

	void rotateLeft(BinaryNode * & rt){

		if (rt->right == NULL)return;

		// keep right child
		BinaryNode* newRoot = clone(rt->right);
		newRoot->size = rt->size;

		// old root is new root's left child
		newRoot->left = rt;

		int tempSize = newRoot->size;

		newRoot->size = rt->size;

		// oldRoot lost one child -> new root
		rt->size = tempSize;

		// set new root
		this->root = newRoot;

		cout << "rotate left" << endl;
	}

	void rotateToRoot(BinaryNode * & node){

		//if (node == NULL)
		//	return;

		if (node == root)
			return;

		// zig right
		if (root->left == node)
			rotateRight(root);

		// zig left
		else if (root->right == node)
			rotateLeft(root);

		// zig zag left
		else if (root->right != NULL && root->right->left == node){
			rotateRight(root->right);
			rotateLeft(node);
		}

		// zig zag right
		else if (root->left != NULL && root->left->right == node){
			rotateLeft(root->left);
			rotateRight(node);
		}

		else if (node->element < root->element)
			rotateToRoot(root->left);

		else
			rotateToRoot(root->right);
	}

	/*void rotateLeft(BinaryNode * & t){
		BinaryNode* tempNode = t->right;
		if (tempNode == NULL) return;
		t->right = tempNode->left;
		tempNode->left = t;
		tempNode->size = t->size;
		updateSize(t);
		cout << "rotate left" << endl;
		}*/

	void printLevel(BinaryNode * & t, int level){

		if (t == NULL)  return;

		if (level == 0){
			cout << " " << t->element;
		}

		else if (level > 0){
			printLevel(t->left, level - 1);
			printLevel(t->right, level - 1);
		}
	}

	unsigned int getSize(BinaryNode* node){
		if (node == NULL)
			return 0;
		else
			return node->size;
	}

	void updateSize(BinaryNode* node){
		node->size = getSize(node->left) + getSize(node->right) + 1;
	}

	int getHeight(BinaryNode * & t){

		if (t == NULL)
			return 0;

		else {

			int leftHeight = getHeight(t->left);
			int rightHeight = getHeight(t->right);

			if (leftHeight < rightHeight)
				return (rightHeight + 1);
			else
				return (leftHeight + 1);
		}
	}

	unsigned int getChildCount(BinaryNode * & t) {

		unsigned int size = 0;

		countChild(t, size);

		return size;
	}

	void countChild(BinaryNode * & t, unsigned int& size){
		if (t == NULL) { return; }

		if (t->left != NULL){
			size++;
			countChild(t->left, size);
		}

		if (t->right != NULL){
			size++;
			countChild(t->right, size);
		}
	}


	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void remove(const Comparable & x, BinaryNode * & t)
	{
		if (t == NULL)
			return;   // Item not found; do nothing
		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != NULL && t->right != NULL) // Two children
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode *oldNode = t;
			t = (t->left != NULL) ? t->left : t->right;
			delete oldNode;
		}
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	BinaryNode * findMin(BinaryNode *t) const
	{
		if (t == NULL)
			return NULL;
		if (t->left == NULL)
			return t;
		return findMin(t->left);
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	BinaryNode * findMax(BinaryNode *t) const
	{
		if (t == NULL)
			return NULL;
		if (t->right == NULL)
			return t;
		return findMax(t->right);
	}


	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the subtree.
	 */
	bool contains(const Comparable & x, BinaryNode *t) const
	{
		if (t == NULL)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}
	/****** NONRECURSIVE VERSION*************************
		bool contains( const Comparable & x, BinaryNode *t ) const
		{
		while( t != NULL )
		if( x < t->element )
		t = t->left;
		else if( t->element < x )
		t = t->right;
		else
		return true;    // Match

		return false;   // No match
		}
		*****************************************************/

	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty(BinaryNode * & t)
	{
		if (t != NULL)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = NULL;
	}

	/**
	 * Internal method to print a subtree rooted at t in sorted order.
	 */
	void printTree(BinaryNode *t, ostream & out) const
	{
		if (t != NULL)
		{
			printTree(t->left, out);
			out << t->element << endl;
			printTree(t->right, out);
		}
	}

	/**
	 * Internal method to clone subtree.
	 */
	BinaryNode * clone(BinaryNode *t) const
	{
		if (t == NULL)
			return NULL;
		else
			return new BinaryNode(t->element, clone(t->left), clone(t->right
			));
	}
};


#endif
