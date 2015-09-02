pyvm: pyvm.c stack.o operations.o init.o pyvm.h opcodes.h
	cc -g -w pyvm.c stack.o operations.o init.o -o pyvm
stack.o: stack.c
	gcc -g -w -c stack.c
operations.o: operations.c 
	gcc -g -w -c operations.c
init.o: init.c opcodes.h
	gcc -g -w -c init.c    
clean:
	rm -f pyvm
	rm -f *.o
	rm -f *.gch
