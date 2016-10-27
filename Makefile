FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
COMPILLER=g++

all: start

start: dictionary.o main.o
	$(COMPILLER) $(FLAGS) -o da-lab2 dictionary.o main.o

main.o: main.cpp
	$(COMPILLER) -c $(FLAGS) main.cpp

dictionary.o: dictionary.cpp
	$(COMPILLER) -c $(FLAGS) dictionary.cpp

clear:
	-rm -f *.o *.gch da-lab2


