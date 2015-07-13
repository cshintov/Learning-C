//replace multiple blanks with a single blank
#include <stdio.h>

main(){
    int chr;
    while((chr = getchar()) != EOF){
        putchar(chr);
        if(chr == ' '){
            while(chr == ' '){
                chr = getchar();
            }
            if(chr == EOF)
                break;
            putchar(chr);
        }
    }
}
