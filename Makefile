all: myls

myls: myls.c arguements.c directory.c printer.c sort.c
	gcc -o myls myls.c arguements.c directory.c printer.c sort.c

valgrind:
	valgrind ./myls

clean:
	rm myls