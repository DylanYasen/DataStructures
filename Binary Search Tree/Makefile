driver.out: BinarySearchTree.h driver.o
	g++ -ansi -Wall BinarySearchTree.h driver.o -o driver.out

#BinarySearchTree.o: BinarySearchTree.h
#	g++ -ansi -Wall -c BinarySearchTree.h

driver.o: driver.cpp
	g++ -ansi -Wall -c driver.cpp

clean:
	rm -f *.o driver.out *~ *.gch

run:
	./driver.out