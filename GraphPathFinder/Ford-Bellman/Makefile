CC=g++
CFLAGS=-std=c++11
SOURCE=ford-bellman.cpp
LIBNAME=libford-bellman.so

.PHONY: all

all: $(LIBNAME)

$(LIBNAME): dynamic.o
	$(CC) -shared dynamic.o -o $(LIBNAME)
	rm *.o

dynamic.o:
	$(CC) -fPIC -c $(SOURCE) -o dynamic.o 

clean:
	rm *.o *.so
