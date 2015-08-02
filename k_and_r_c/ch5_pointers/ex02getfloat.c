// getch function used by getop function

#include <stdio.h>

int main(){
    
    double num;
    getfloat(&num);
    printf("The number is : %f\n", num);
    return 0;
}

void ungetch(int);
int getch(void);

int getfloat(double *pnum) {
    int chr, sign;
    float power = 1.0;
    while((chr = getch()) == ' ' || chr == '\t')
        ;
    sign = (chr == '-') ? -1 : 1;
    if(chr == '+' || chr == '-')
        chr = getch();

    for(*pnum=0.0; isdigit(chr); chr = getch())
        *pnum = 10 * *pnum + (chr - '0');
    
    if(chr == '.') {
        chr = getch();
        for(; isdigit(chr); chr = getch(),power *= 10)
            *pnum = 10 * *pnum + (chr - '0');
    }
    *pnum *= sign / power;
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
