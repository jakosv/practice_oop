CC=g++
CFLAGS=-std=c++11
SOURCE=dijkstra.cpp
LIBNAME=libdijkstra.so

.PHONY: all clean

all: $(LIBNAME)

$(LIBNAME): dynamic.o
	$(CC) -shared dynamic.o -o $(LIBNAME)
	rm *.o

dynamic.o:
	$(CC) -fPIC -c $(SOURCE) -o dynamic.o 

clean:
	rm *.o *.so
