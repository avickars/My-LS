all: myls

myls: myls.c
	gcc -o myls myls.c

clean:
	rm myls