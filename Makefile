CPP=g++
STD=c++17

all : src/poka.cpp
	$(CPP) -std=$(STD) -o poka src/poka.cpp

.PHONY: clean clobber

clean:
	rm -fr ./poka

