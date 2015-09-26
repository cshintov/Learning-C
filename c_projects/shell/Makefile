shell: shell.c utils.o utils.h
	gcc -g shell.c utils.o -o shell
	echo type make run to launch the shell
CFLAGS = -g
temp: temp.c utils.o utils.h
	gcc -g temp.c utils.o utils.h -o temp
utils.o: utils.h

clean:
	rm -f *.o
	rm -f shell a.out

run:
	./shell
