CXXFLAGS = -Wall -ansi -g
OBJS = Driver.cpp IntervalHeap.cpp IntervalHeap.h

all:
	g++ $(CXXFLAGS) $(OBJS) -o Proj4
run:
	./Proj4 $(MIN) $(MAX) $(SIZE) $(SEED)

clean:
	rm results.txt Proj4 