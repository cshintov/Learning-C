//equivalent loop without && or ||

#include <stdio.h>
#define MAX 1000
main() {
    int i, c, lim;
    char s[MAX];

    lim = MAX;
    //for(i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; i++) s[i] = c;
    i = 0;
    while ( i < lim -1) {
        if((c = getchar()) == '\n')
            break;
        if(c == EOF)
            break;
        s[i] = c;
        i++;
    }
}
