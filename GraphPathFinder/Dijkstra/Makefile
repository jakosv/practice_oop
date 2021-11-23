CXX=c++
CXXFLAGS=-std=c++11
SOURCE=dijkstra.cpp
LIBNAME=libdijkstra.so

.PHONY: all clean

all: $(LIBNAME)

$(LIBNAME): dynamic.o
	$(CXX) -shared dynamic.o -o $(LIBNAME)

dynamic.o:
	$(CXX) -fPIC -c $(SOURCE) -o dynamic.o $(CXXFLAGS)

clean:
	rm *.o *.so
