//counts the number of lines

#include <stdio.h>

main(){
    int chr, num_line;
    num_line = 0;
    while((chr = getchar()) != EOF){
        if(chr == '\n')
            ++num_line;
    }
    printf("number of lines : %d", num_line);
}
