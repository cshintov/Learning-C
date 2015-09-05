shell: shell.c utils.o utils.h
	gcc -g shell.c utils.o -o shell
CFLAGS = -g
utils.o: utils.h

clean:
	rm -f *.o
	rm -f shell

run:
	./shell
