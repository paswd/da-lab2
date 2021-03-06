FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
COMPILLER=g++

all: lib start

start: main.o
	$(COMPILLER) $(FLAGS) -o da-lab2 main.o -L. lib/lib-btree.a

main.o: main.cpp
	$(COMPILLER) -c $(FLAGS) main.cpp


btree.o: btree.cpp
	$(COMPILLER) -c $(FLAGS) btree.cpp

clear:
	-rm -f *.o *.gch da-lab2
	rm lib/lib-btree.a

lib: btree.o
	ar rc lib/lib-btree.a btree.o
	ranlib lib/lib-btree.a
