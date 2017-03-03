#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "IntervalHeap.h"
using namespace std;

//prints username and section
void greeting() {
	cout << "Yadikaer Yasheng" << endl;
	cout << "Section 3" << endl;
}

//main method that calls appropriate methods to built the interval heap, iteraltively delete min-max from the interval heap and print results to the results.txt file 
int main(int argc, char * argv[]) {

  greeting();

  // get input
  int min = atoi(argv[1]);
  int max = atoi(argv[2]);
  int size = atoi(argv[3]);
  int seed = atoi (argv[4]);

  //IntervalHeap heap(0, 100, 8, 123456789);
  //IntervalHeap heap(-50, 100, 11, 123456);
  IntervalHeap heap(min,max,size,seed);

  heap.insertRandomNumbers();
  
  ofstream file("results.txt");
  
  file << "min=" << min << " max=" << max << " size=" << size << " seed=" << seed << endl << endl;  
  
  file << "Interval Heap Built:" << endl << endl;
  
  heap.printIntervalHeap(file);

  heap.deleteMinMaxIteratively(file);
  
  file.close();
}
