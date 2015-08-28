pyvm: pyvm.c optab.o utils.o stack.o operations.o init.o utils.h opcodes.h
	cc -g pyvm.c optab.o utils.o stack.o operations.o init.o -o pyvm
optab.o: optab.c utils.h
	gcc -g -c optab.c 
utils.o: utils.c utils.h
	gcc -g -c utils.c
stack.o: stack.c
	gcc -g -c stack.c
operations.o: operations.c 
	gcc -g -c operations.c
init.o: init.c opcodes.h
	gcc -g -c init.c    
clean:
	rm -f pyvm
	rm -f *.o
	rm -f *.gch
