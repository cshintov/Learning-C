// implement qsort1 case insensitive

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right, 
           int (*comp)(void *, void*));
int numcmp(const char*, const char*); // const because strcmp uses const
                                      // and ?: needs both be same type

int numcmpr(const char* str1, const char* str2); 
int strcmpr(const char* str1, const char* str2); 
int strcmpf(const char* str1, const char* str2); 
int strcmpfr(const char* str1, const char* str2); 
int type(int num, int rev, int fold);

int main(int argc, char *argv[]) 
{
    int nlines, option;
    int numeric = 0, reverse = 0, fold = 0;

    while(--argc > 0 && (*++argv)[0] == '-') 
        while(option = *++argv[0]) {
            switch(option) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                case 'f':
                    fold = 1;
                    break;
                default:
                    printf("error: invalid option\n");
                    break;
            }
        }

    option = type(numeric, reverse, fold);
    printf("%d is the option \n", option);
    if((nlines = readlines(lineptr, MAXLINES)) > 0) {
        switch(option){
            case 1:
                qsort1((void **)lineptr, 0, nlines-1,
                (int (*) (void*, void*)) strcmp);
                break;
            case 2:
                qsort1((void **)lineptr, 0, nlines-1,
                (int (*) (void*, void*))strcmpr);
                break;
            case 3:
                qsort1((void **)lineptr, 0, nlines-1,
                (int (*) (void*, void*))(strcmpf));
                break;
            case 4:
                qsort1((void **)lineptr, 0, nlines-1,
                (int (*) (void*, void*))(strcmpfr));
                break;
            case 5:
                qsort1((void **)lineptr, 0, nlines-1,
                (int (*) (void*, void*))(numcmp));
                break;
            case 6:
                qsort1((void **)lineptr, 0, nlines-1,
                (int (*) (void*, void*))(numcmpr));
                break;
            default:
                printf("invalid option\n");
                break;
        }
        printf("\nafter sorting \n");
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: input  too big to sort\n");
        return 1;
    }
}


int type(int num, int rev, int fold)
{
    int option;
    if(num) {
        if(rev)
            option = 6;
        else
            option = 5;
    } else {
        if(rev)
            if(fold)
                option = 4;
            else
                option = 2;
        else
            if(fold)
                option = 3;
            else
                option = 1;
    }
    return option;
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

void qsort1(void *v[], int  left, int right, int (*comp)(void *, void *)) 
{
    int i, last;
    void swap(void *v[], int i, int j);
    if(left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;

    for(i=left+1; i<=right; i++) {
        if(((*comp)(v[i], v[left]) < 0))
            swap(v, ++last, i);
    }

    swap(v, left, last);
    qsort1(v, left, last-1, comp);
    qsort1(v, last+1, right, comp);
}

void swap(void *v[], int i, int j)
{
    char *temp;
    temp =  v[i];
    v[i] = v[j];
    v[j] = temp;
}

#include <stdlib.h>

int numcmp(const char* str1, const char* str2) 
{
    double v1, v2;
    v1 = atof(str1);
    v2 = atof(str2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
} 

int numcmpr(const char* str1, const char* str2) {
    return -1 * numcmp(str1, str2);
}

int strcmpr(const char* str1, const char* str2) {
    return -1 * strcmp(str1, str2);
}

char *strlwr(char *str);
int strcmpf(const char* str1, const char* str2) {
    return strcasecmp(str1, str2);
}

int strcmpfr(const char* str1, const char* str2) {
    return -1 * strcmpf(str1, str2);
}

#include<ctype.h>

char *strlwr(char *str)
{
    size_t i;
    size_t len = strlen(str);

    for(i=0; i<len; i++)
    str[i]=tolower((unsigned char)str[i]);

    return str;
}
