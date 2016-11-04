FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -std=c++11
COMPILLER=g++

#all: lib start
all: start

#start: main.o
#	$(COMPILLER) $(FLAGS) -o da-lab2 main.o -L. lib/lib-btree.a

start: btree.o main.o
	$(COMPILLER) $(FLAGS) -o da-lab2 btree.o main.o

main.o: main.cpp
	$(COMPILLER) -c $(FLAGS) main.cpp


btree.o: btree.cpp
	$(COMPILLER) -c $(FLAGS) btree.cpp

clear:
	-rm -f *.o *.gch *.dat da-lab2
	#rm lib/lib-btree.a

lib: btree.o
	ar rc lib/lib-btree.a btree.o
	ranlib lib/lib-btree.a
