all: Driver.o QuadraticProbing.o TextFile.o
	g++ Driver.o QuadraticProbing.o TextFile.o -o proj5.out

Driver.o: Driver.cpp
	g++ -c Driver.cpp

QuadraticProbing.o: QuadraticProbing.cpp
	g++ -c QuadraticProbing.cpp

TextFile.o: TextFile.cpp
	g++ -c TextFile.cpp

run:
	./proj5.out $(DIR)

clean:
	rm -rf *.o
	rm -f proj5.out
	rm -f *~ *.h.gch *#
	rm -rf *.txt