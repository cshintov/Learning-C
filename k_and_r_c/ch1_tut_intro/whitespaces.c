//counts blanks, tabs, and newlines
#include <stdio.h>

main(){
    int blk, tab, nwl, chr;
    blk = tab = nwl = 0;
    while((chr = getchar()) != EOF){
        if(chr == '\n')
            nwl++;
        if(chr == '\t')
            tab++;
        if(chr == ' ')
            blk++;
    }
    printf("\nThere are %d blanks, %d tabs, %d newlines", blk, tab, nwl);
    printf("\nThere are %d whitespaces in total",blk + tab + nwl);
}
