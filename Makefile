# CPP=g++
CPP=clang++
STD=c++20

all : src/poka.cpp
	$(CPP) -std=$(STD) -o poka src/poka.cpp

.PHONY: clean clobber

clean:
	rm -fr ./poka

