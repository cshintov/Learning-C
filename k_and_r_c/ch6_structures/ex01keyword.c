// count c keywords
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "define", 0,
    "float", 0,
    "for", 0,
    "int", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

#define NKEYS ( sizeof(keytab) / sizeof(keytab[0]) )

int getword(char *, int);
int binsearch(char *, struct key *, int);

int main(void)
{
    char word[MAXWORD];
    int n;

    while(getword(word, MAXWORD) != EOF)
        if(isalpha(word[0]))
            if((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for(n = 0; n < NKEYS; n++) 
        if(keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    
    return 0;
}

int binsearch(char *word, struct key tab[], int n)
{
    int low, mid, high;
    int cond;

    low = 0;
    high = n - 1;
    while(low <= high) {
        mid = (low + high) / 2;
        if((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if(cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
int skipcomment(int);
int getword(char *word, int lim)
{
    int getch(void), c;
    void ungetch(int);
    char *w = word;

    while(isspace(c = getch()))
        ;
    c = skipcomment(c);
    if(c == '#')    
        while((c = getch()) != '\n' )
            ;
    if(c == '_')    
        while(!isspace(c = getch()))
            ;
    if(c != EOF)
        *w++ = c;
    if(!isalpha(c)){
        *w = '\0';
        return c;
    }
    for(; --lim > 0; w++)
        if(!isalnum(*w = getch())){
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

int skipcomment(int c)
{
    int getch(void), end = 0;
    void ungetch(int);
    if(c != '/')
        return c;
    if((c = getch()) == '*') {
        while(!end) {
            while((c = getch()) != '*')
                ;
            if((c = getch()) == '/')
                end = 1;
            else
                ungetch(c);
        }
    } else if(c == '/') {
        while((c = getch()) != '\n')
            if(c == EOF)
                return c;
        end = 1;
    }
    if(end)
        return getch();
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();   
}

void ungetch(int c) {
    if(bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch : Too many values!\n");
}
