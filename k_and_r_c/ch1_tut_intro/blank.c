//replace multiple blanks with a single blank
#include <stdio.h>

main(){
    int chr;
    chr = getchar();
    while(chr != EOF){
        putchar(chr);
        if(chr == ' '){
            while(chr == ' '){
                chr = getchar();
            }
            if(chr != EOF)
                putchar(chr);
        }
    }
}
