FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
COMPILLER=g++

all: start

start: btree.o main.o
	$(COMPILLER) $(FLAGS) -o da-lab2 btree.o main.o

main.o: main.cpp
	$(COMPILLER) -c $(FLAGS) main.cpp


btree.o: btree.cpp
	$(COMPILLER) -c $(FLAGS) btree.cpp

clear:
	-rm -f *.o *.gch da-lab2


