
all : baseconv

baseconv.o : baseconv.c
	gcc -c baseconv.c -Wall -Werror -Os -o baseconv.o

baseconv : baseconv.o
	gcc baseconv.o -Wall -Werror -Os -o baseconv

clean :
	rm -f *.o 
	rm -f baseconv

install :
	cp baseconv /usr/local/bin/baseconv

uninstall :
	rm -f /usr/local/bin/baseconv

test : baseconv
	./baseconv

