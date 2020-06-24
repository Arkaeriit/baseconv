
FLAGS = -Wall -Wextra -g
#FLAGS = -Os

all : baseconv

baseconv.o : baseconv.c
	gcc -c baseconv.c $(FLAGS) -o baseconv.o

baseconv : baseconv.o
	gcc baseconv.o $(FLAGS) -o baseconv

clean :
	rm -f *.o 
	rm -f baseconv

install :
	cp baseconv /usr/local/bin/baseconv

uninstall :
	rm -f /usr/local/bin/baseconv

test : baseconv
	./baseconv

