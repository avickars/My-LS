all: myls

myls: myls.c arguements.c directory.c printer.c sort.c list.c
	gcc -o myls myls.c arguements.c directory.c printer.c sort.c list.c

valgrind:
	valgrind --leak-check=full --track-origins=yes -s ./myls fdsa *

clean:
	rm myls