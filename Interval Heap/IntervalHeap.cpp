#include <stdlib.h>
#include <iostream>
#include "IntervalHeap.h"
using namespace std;

//Constructor
IntervalHeap::IntervalHeap(int min, int max, int inpSize, int seed) {

	this->inputSize = inpSize;

	// set range
	this->minRange = min;
	this->maxRange = max;

	// set seed
	this->seed = seed;

	// array size
	// 10 input needs 5 slots
	int arrSize = inputSize / 2 + inputSize % 2;
	arrSize++;	// [0] is garbage

	//cout << arrSize << endl;

	heap = new LeftRightElements[arrSize];

	currentSize = 0;
}

//Destructor
IntervalHeap::~IntervalHeap() {
	delete[] heap;
}

//returns min from interval heap
int IntervalHeap::getMin() {
	return heap[1].left;
}

//returns max from interval heap
int IntervalHeap::getMax() {
	return heap[1].right;
}

//returns total number of elements in the interval heap 
int IntervalHeap::getSize() {
	return currentSize;
}

//method that generates random numbers and inserts them in the interval heap
void IntervalHeap::insertRandomNumbers() {
	srand(this->seed);

	ofstream d;

	for (int i = 0; i < inputSize; i++) {
		// get a random number
		int num = (rand() % (maxRange - minRange)) + minRange;

		insert(num);
	}
}

//method that inserts an element into the interval heap
void IntervalHeap::insert(int num) {

	// no parent situation
	if (currentSize < 2) {

		// empty
		if (currentSize == 0) {

			// [0] is reserved
			heap[1].left = num;
			heap[1].right = num;
		}

		// one node
		else {
			if (num < heap[1].left)
				heap[1].left = num;
			else
				heap[1].right = num;
		}

		currentSize++;
		return;
	}

	// last node 
	int lastNodeIndex = currentSize / 2 + currentSize % 2;

	////cout << "last node index " << lastNodeIndex << endl;
	////cout << "current size " << currentSize << endl;

	// even size check parent
	if (currentSize % 2 == 0) {

		// new slot
		lastNodeIndex++;
		//cout << "even size ,last node index " << lastNodeIndex << endl;

		// 2parent + 1 = child
		// parent = (child-1) / 2
		// get x's parent.
		////cout << "parent index " << lastNodeIndex/2 << endl;
		LeftRightElements parent = heap[lastNodeIndex / 2];
		////cout << "parent left: "<<parent.left<<" right: "<<parent.right<<endl;

		heap[lastNodeIndex].left = num;
		heap[lastNodeIndex].right = num;

		currentSize++;

		if (num < parent.left)
			fixMinHeap(num, lastNodeIndex);

		else
			fixMaxHeap(num, lastNodeIndex);

	}

	// odd size check last node
	else {

		////cout << "odd size" << endl;

		currentSize++;

		if (num < heap[lastNodeIndex].left) {
			heap[lastNodeIndex].left = num;

			fixMinHeap(num, lastNodeIndex);
		} else {
			heap[lastNodeIndex].right = num;

			fixMaxHeap(num, lastNodeIndex);
		}

	}
}

// 2parent + 1 = child
// parent = (child-1) / 2
// get x's parent
void IntervalHeap::fixMaxHeap(int num, int index) {

	int parentIndex = index / 2;

	////cout << "fix max heap, parent is "<< parentIndex<<endl;

	//ofstream s;
	//printIntervalHeap(s);

	// heap[1] 
	if (index == 1 || num <= heap[parentIndex].right) {
		heap[index].right = num;

		if (currentSize % 2 == 1) {
			int lastNodeIndex = currentSize / 2 + currentSize % 2;

			// //cout << "set last node. it's index is " << lastNodeIndex << " left:"<<heap[lastNodeIndex].left<<" right:"<<heap[lastNodeIndex].right<<endl;

			heap[lastNodeIndex].left = heap[lastNodeIndex].right;
		}

		return;
	}

	//else if (num <= heap[parentIndex].right)
	//	return;

	// swap
	//int reservedParentRight = heap[parentIndex].right;
	//heap[parentIndex].right = num;
	////cout << heap[index].right << " changes to "<<heap[parentIndex].right<<endl;

	//if(heap[index])

	heap[index].right = heap[parentIndex].right;

	// update index
	index = parentIndex;

	fixMaxHeap(num, index);
}

// 2parent + 1 = child
// parent = (child-1) / 2
// get x's parent
void IntervalHeap::fixMinHeap(int num, int index) {

	int parentIndex = index / 2;

	////cout << "fix min heap, parent is "<< parentIndex<<endl;

	// heap[1] 
	if (index == 1 || num >= heap[parentIndex].left) {

		heap[index].left = num;

		if (currentSize % 2 == 1) {
			int lastNodeIndex = currentSize / 2 + currentSize % 2;

			heap[lastNodeIndex].right = heap[lastNodeIndex].left;
		}

		return;
	}
	//else if (num >= heap[parentIndex].left)
	//return;

	// swap
	//int reservedParentLeft = heap[parentIndex].left;
	//heap[parentIndex].left = num;

	////cout <<heap[index].left << " changes to "<<heap[parentIndex].left<<endl;
	heap[index].left = heap[parentIndex].left;

	// update index
	index = parentIndex;

	fixMinHeap(num, index);
}

// 2parent + 1 = child
void IntervalHeap::fixMaxHeapDownWard(int num, int index) {

	int leftChildIndex = 2 * index;
	int rightChildIndex = 2 * index + 1;

	//cout << "left child index is " << leftChildIndex << " value: "
	//<< heap[leftChildIndex].right << endl;
	//cout << "right child index is " << rightChildIndex << " value: "
	//<< heap[rightChildIndex].right << endl;

	//cout << " index is " << index << " value is " << heap[index].right << endl;

	//ofstream s;
	//printIntervalHeap(s);

	// child out of bound
	if (leftChildIndex >= currentSize / 2 + currentSize % 2) {

		//cout << "child out of bound new " << endl;

		//cout << "last node index " << currentSize / 2 + currentSize % 2 << endl;
		// last node
		if (index == currentSize / 2 + currentSize % 2 + 1) {

			//cout << "this is last node" << endl;
			// even size, have right child
			// swap
			if (currentSize % 2 == 0) {

				if (heap[index].left > heap[index].right) {
					int reserve = heap[index].right;
					heap[index].right = heap[index].left;
					heap[index].left = reserve;
				}
			}

			// odd size set right
			else {
				//cout << "odd size set right " << endl;
				heap[index].left = heap[index].right;
			}
		}

		// middle nodes
		else if (heap[index].left > heap[index].right) {
			int reserve = heap[index].right;
			heap[index].right = heap[index].left;
			heap[index].left = reserve;
		}

		return;
	} else if (num >= heap[leftChildIndex].right
			&& num >= heap[rightChildIndex].right) {

		// maintain left <= right
		if (heap[index].left > heap[index].right) {
			int reserve = heap[index].right;
			heap[index].right = heap[index].left;
			heap[index].left = reserve;
		}

		return;
	}

	int childIndex = 0;
	if (heap[leftChildIndex].right > heap[rightChildIndex].right) {
		childIndex = leftChildIndex;
		//cout << "go left" << endl;
	}

	else if (heap[rightChildIndex].right > heap[leftChildIndex].right
			&& rightChildIndex <= currentSize / 2 + currentSize % 2) {
		childIndex = rightChildIndex;
		//cout << "go right" << endl;
	}

	else
		childIndex = leftChildIndex;

	//cout << "index " << index << "swap with " << childIndex << endl;

	// swap
	int reservedChildRight = heap[childIndex].right;
	heap[childIndex].right = num;
	heap[index].right = reservedChildRight;

	// update index
	index = childIndex;

	fixMaxHeapDownWard(num, index);

}

// 2parent + 1 = child
void IntervalHeap::fixMinHeapDownWard(int num, int index) {

	int leftChildIndex = 2 * index;
	int rightChildIndex = 2 * index + 1;

	//cout << "left child index is " << leftChildIndex << " value: "
	//<< heap[leftChildIndex].left << endl;
	//cout << "right child index is " << rightChildIndex << " value: "
	//<< heap[rightChildIndex].left << endl;

	// last node
	if (leftChildIndex >= currentSize / 2 + currentSize % 2) {

		//cout << index << " children is out of range" << endl;

		// last node
		if (index == currentSize / 2 + currentSize % 2) {

			//cout << " this is last node" << endl;

			// even size, have right child
			// swap
			if (currentSize % 2 == 0) {

				if (heap[index].left > heap[index].right) {
					int reserve = heap[index].right;
					heap[index].right = heap[index].left;
					heap[index].left = reserve;
				}
			}
			// odd size set righ
			else
				heap[index].right = heap[index].left;
		}

		else if (heap[index].left > heap[index].right) {
			int reserve = heap[index].right;
			heap[index].right = heap[index].left;
			heap[index].left = reserve;
		}

		//cout << "child index out of range. return " << endl;
		return;
	}

	else if (num <= heap[leftChildIndex].left
			&& num <= heap[rightChildIndex].left) {

		// maintain left <= right
		if (heap[index].left > heap[index].right) {
			int reserve = heap[index].right;
			heap[index].right = heap[index].left;
			heap[index].left = reserve;
		}

		//cout << "already less than child,return" << endl;

		return;
	}

	int childIndex = 0;
	if (heap[rightChildIndex].left > heap[leftChildIndex].left)
		childIndex = leftChildIndex;
	else if (heap[rightChildIndex].left < heap[leftChildIndex].left
			&& rightChildIndex <= currentSize / 2 + currentSize % 2)
		childIndex = rightChildIndex;
	else
		childIndex = leftChildIndex;

	//cout << "index " << index << "swap with " << childIndex << endl;

	// swap
	int reservedChildLeft = heap[childIndex].left;
	heap[childIndex].left = num;
	heap[index].left = reservedChildLeft;

	// update index
	index = childIndex;

	fixMinHeapDownWard(num, index);
}

//method that deletes min and max ieratively until just element is left
void IntervalHeap::deleteMinMaxIteratively(ofstream &f) {

	int reservedCurrentSize = currentSize;
	for (int i = 0; i < reservedCurrentSize / 2; i++) {

	  f << endl<< "After deleting min element: " << heap[1].left <<":" << endl << endl;
	  deleteMin();
	  printIntervalHeap(f);

	  if (currentSize < 2)
	    break;
	  f << endl<< "After deleting max element " << heap[1].right << ":" << endl  << endl;
	  deleteMax();
	  printIntervalHeap(f);
	}
}

//method that deletes min from the interval heap
void IntervalHeap::deleteMin() {

  // get min value
  //int min = heap[1].left;

	// last node 
	int lastNodeIndex = currentSize / 2 + currentSize % 2;

	// decide which one to pull to root
	if (heap[lastNodeIndex].left != heap[lastNodeIndex].right) {
		heap[1].left = heap[lastNodeIndex].right;
		heap[lastNodeIndex].right = heap[lastNodeIndex].left;
	} else {
		heap[1].left = heap[lastNodeIndex].left;
		heap[lastNodeIndex].left = heap[lastNodeIndex].right;
	}

	currentSize--;

	// 2n+1 donesn't apply to root
	// since root at [1]

	int leftChildIndex = 2;
	int rightChildIndex = 3;
	int childIndex = 0;

	// find child to swap
	if (heap[leftChildIndex].left < heap[rightChildIndex].left)
		childIndex = leftChildIndex;
	else if (heap[leftChildIndex].left > heap[rightChildIndex].left
			&& rightChildIndex <= currentSize / 2 + currentSize % 2)
		childIndex = rightChildIndex;
	else
		childIndex = leftChildIndex;

	if (heap[1].left > heap[childIndex].left) {
		// swap
		int reserve = heap[childIndex].left;
		heap[childIndex].left = heap[1].left;
		heap[1].left = reserve;

		fixMinHeapDownWard(heap[childIndex].left, childIndex);
	}
}

//method that deletes max from the interval heap
void IntervalHeap::deleteMax() {

  // get min value
  //int max = heap[1].right;

	// last node 
	int lastNodeIndex = currentSize / 2 + currentSize % 2;

	if (heap[lastNodeIndex].left != heap[lastNodeIndex].right) {
		heap[1].right = heap[lastNodeIndex].right;
		heap[lastNodeIndex].right = heap[lastNodeIndex].left;
	} else {
		heap[1].right = heap[lastNodeIndex].left;
		heap[lastNodeIndex].left = heap[lastNodeIndex].right;
	}

	currentSize--;

	//cout << "root is now " << heap[1].right << endl;

	//	ofstream s;
	//printIntervalHeap(s);

	//currentSize--;

	// 2n+1 donesn't apply to root                                                                                                                              
	// since root at [1]
	int leftChildIndex = 2;
	int rightChildIndex = 3;
	int childIndex = 0;

	//cout << "right child value " << heap[rightChildIndex].right << endl;
	//cout << "left child value " << heap[leftChildIndex].right << endl;

	// find child to swap                                                                                                                                       
	if (heap[leftChildIndex].right > heap[rightChildIndex].right)
		childIndex = leftChildIndex;
	else if (heap[leftChildIndex].right < heap[rightChildIndex].right
			&& rightChildIndex <= currentSize / 2 + currentSize % 2)
		childIndex = rightChildIndex;
	else
		childIndex = leftChildIndex;

	if (heap[1].right < heap[childIndex].right) {
		// swap
		int reserve = heap[childIndex].right;
		heap[childIndex].right = heap[1].right;
		heap[1].right = reserve;

		fixMaxHeapDownWard(heap[childIndex].right, childIndex);
	}
}

//print level order interval heap to results.txt file
void IntervalHeap::printIntervalHeap(ofstream &f) {

  //int parentIndex = 1;

	////cout << currentSize << endl;

	if (currentSize <= 2) {
		f << heap[1].left;

		if (currentSize == 1)
			f << endl;
		else
			f << "," << heap[1].right << endl;
	}

	else {
		for (int i = 1; i < currentSize / 2 + currentSize % 2 + 1; i++) {

			// last node. only one element situation
			if (i == currentSize / 2 + 1 && currentSize % 2 == 1) {
				f << heap[i].left << endl;
			}

			else {
				f << heap[i].left << ",";
				f << heap[i].right << endl;
			}
			//if (i == 2 * parentIndex + 2 || i == 1)
			//	//cout << endl;
		}
	}
}

