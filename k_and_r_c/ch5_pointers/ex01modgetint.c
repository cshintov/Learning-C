// getch function used by getop function

#include <stdio.h>

int main(){
    
    int num, val;
    val = getint(&num);
    printf("The returned value is : %c %d\n", val, val);
    printf("The number is : %d \n", num);
    return 0;
}

void ungetch(int);
int getch(void);

int getint(int *pnum) {
    int chr, sign, temp;
    while((chr = getch()) == ' ' || chr == '\t')
        ;
    sign = (chr == '-') ? -1 : 1;
    if(chr == '+' || chr == '-'){
        if(!isdigit(chr = getch())){
            ungetch(chr);
            return chr;
        }
    }

    for(*pnum=0; isdigit(chr); chr = getch())
        *pnum = 10 * *pnum + (chr - '0');
    
    *pnum *= sign;
    if(chr != EOF)
        ungetch(chr);
    return chr;
}
#define BUFSIZE 100

static char buf[BUFSIZE];
static int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();   
}

void ungetch(int c) {
    if(bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch : Too many values!\n");
}
