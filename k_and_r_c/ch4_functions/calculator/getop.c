// getop function used by calculator main function

#include <stdio.h>
#include <ctype.h>
#include "calculator.h"

int getop(char str[]) {
    int i, c;

    while((str[0] = c = getch()) == ' ' || c == '\t')
        ;
    str[1] = '\0';
    
    if(!isdigit(c) && c != '.')
        return c;

    i = 0;
    if(isdigit(c))
        while(isdigit(str[++i] = c = getch()))
            ;

    if(c == '.')
        while(isdigit(str[++i] = c = getch()))
            ;

    str[i] = '\0';
    if(c != EOF)
        ungetch(c);

    return NUMBER;
}
