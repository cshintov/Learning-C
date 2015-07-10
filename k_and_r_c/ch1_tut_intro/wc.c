// count lines, words, characters

#include <stdio.h>
#define IN 1
#define OUT 0
main(){
    int chr, lines, words, chars, state;
    lines = words = chars = 0;
    state = OUT;
    while((chr = getchar()) != EOF){
        chars++;
        if(chr == '\n')
            lines++;
        //loop runs without adding word count    
        if(chr == ' ' || chr == '\n' || chr == '\t'){
            state = OUT;
        }
        //if chr is nonspace and state is out this is a word
        else if(state == OUT){
            words++;
            state = IN;
        }
    }
    printf("characters %d, words %d, lines %d", chars, words, lines);
}
