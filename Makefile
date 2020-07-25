all: myls

myls: myls.c arguements.c directory.c printer.c
	gcc -o myls myls.c arguements.c directory.c printer.c

valgrind:
	valgrind ./myls

clean:
	rm myls