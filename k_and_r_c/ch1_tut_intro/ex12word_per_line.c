// prints one word per line

#include <stdio.h>
#define IN 1
#define OUT 0
main(){
    int chr, state;
    state = OUT;
    while((chr = getchar()) != EOF){
        if(chr == ' ' || chr == '\n' || chr == '\t'){
            //marks the last character of the word and prints the newline
            if(state == IN)
                putchar('\n');
            state = OUT;
        }
        //if chr is nonspace and state is out this is the start of the word
        else if(state == OUT)
            state = IN;
        //prints the characters inside the word
        if(state == IN)
            putchar(chr);
    }
}
