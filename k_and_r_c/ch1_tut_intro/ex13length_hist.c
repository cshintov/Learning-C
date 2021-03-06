// print word length histogram

#include <stdio.h>
#define IN 1
#define OUT 0
main(){
    int chr, state, length;
    int number[50], i;
    
    for(i = 0; i < 50; i++){
        number[i] = 0;
    }

    state = OUT;
    length = 0;
    while((chr = getchar()) != EOF){
        if(chr == ' ' || chr == '\n' || chr == '\t'){
            //marks the last character of the word 
            if(state == IN){
                number[length]++;
                length = 0;
            }
            state = OUT;
        }
        //if chr is nonspace and state is out this is the start of the word
        else if(state == OUT)
            state = IN;
        //counts the length of the word
        if(state == IN){
            length++;
        }
    }
    
    printf("length - number of words");
    printf("\n");

    //prints the histogram 
    for(length = 1; length < 25; length++){
        if(number[length] > 0){
            printf("%5d -%3d ",length, number[length]);
            for(i = 0; i < number[length]; i++)
                printf("%2s", "#");
            printf("\n");
        }
    }
}
