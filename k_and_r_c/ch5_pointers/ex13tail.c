// implement qsort

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main(int argc, char *argv[]) 
{
    int nlines;
    if((nlines = readlines(lineptr, MAXLINES)) > 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: input  too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000

char *alloc(int n);
int mygetline(char *s, int lim);

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    
    nlines = 0;
    while((len = mygetline(line, MAXLEN)) > 0) {
        if(nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;
    
    for(i=0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int mygetline(char *s, int lim) {
    char *start = s;
    int chr;
    while(lim-- > 0 && (chr = getchar()) != EOF && chr != '\n')
        *s++ = chr;
    if(chr == '\n')
        *s++ = chr;
    *s = '\0';
    return s - start ;
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if((allocbuf + ALLOCSIZE - allocp) >= n) {
        allocp += n;
        return allocp - n;
    } else
        return 0;
}

void free(char *p) 
{
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

void qsort(char *v[], int  left, int right) 
{
    int i, last;
    void swap(char *v[], int i, int j);
    if(left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;

    for(i=left+1; i<=right; i++) {
        if((strcmp(v[i], v[left]) < 0))
            swap(v, ++last, i);
    }

    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;
    temp =  v[i];
    v[i] = v[j];
    v[j] = temp;
}
