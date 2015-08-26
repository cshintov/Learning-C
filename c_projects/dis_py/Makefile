dis: dis.c optab.o utils.o
	cc -g dis.c optab.o utils.o -o dis
optab.o: optab.c 
	gcc -g -c optab.c -o optab.o
utils.o: utils.c
	gcc -g -c utils.c
clean:
	rm -f dis
	rm -f *.o
	rm -f *.gch
