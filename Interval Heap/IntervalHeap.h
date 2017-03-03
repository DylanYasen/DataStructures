#include <fstream>
using namespace std;

class LeftRightElements {

public:
	int left;
	int right;
};

class IntervalHeap{
public:
	IntervalHeap(int min, int max, int size, int seed);
	~IntervalHeap();
	int getMin();
	int getMax();
	int getSize();
	void insertRandomNumbers();
	void insert(int num);
	void deleteMinMaxIteratively(ofstream &f);
	void deleteMin();
	void deleteMax();
	void printIntervalHeap(ofstream &f);
private:
	LeftRightElements *heap;/*array to maintain heap structure*/
	int currentSize;/*total number of elements in the interval heap*/
	int inputSize;/*the one that is provided with make run command*/
	int minRange;/*the one that is provided with make run command*/
	int maxRange;/*the one that is provided with make run command*/
	int seed;/*the one that is provided with make run command*/



	void fixMinHeap(int num, int index);
	void fixMaxHeap(int num, int index);

	void fixMinHeapDownWard(int num, int index);
	void fixMaxHeapDownWard(int num, int index);

	void printLevel();

};
