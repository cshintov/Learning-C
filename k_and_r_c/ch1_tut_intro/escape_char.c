// replace tabs, backspace, backslashes with the escape characters

#include <stdio.h>

main(){
    int chr;
    while((chr = getchar()) != EOF){
        if(chr == '\t')
            printf("\\t");
        else if(chr == '\\')
            printf("\\\\");
        else if(chr == '\b')
            printf("\\b");
        else
            putchar(chr);
    }
}
