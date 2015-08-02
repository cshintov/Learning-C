// versions of standard libraries strcat, strcpy, strcmp

#include <stdio.h>
#define TRUE  1
#define FALSE 0

char *strcpy(char *s, char *t, int n);
char *strcat(char *s, char *t, int n);
int strcmp(char *s, char *t, int n);
int main() {
    char s[50] = "shanto";
    char t[50] = "shb";
    int res;
    res = strcmp(t,s, 4);
    if(res < 0)
        printf("less than\n");
    else if(res == 0)
        printf("equal\n");
    else
        printf("greater than\n");
        
    return 0;
}

char *strcpy(char *s, char *t, int n) {
    int i = 0;
    int end = FALSE;

    while(i++ < n) {
        if(*t == '\0')
            end = TRUE;
        if(end) 
            *s++ = '\0';
        else
            *s++ = *t++;
    }
    return s-n;
}

char *strcat(char *s, char *t, int n) {
    int i = 0;
    int end = FALSE;
    char *start = s;
    while(*s++)
        ;
    s--;

    while(i++ < n) {
        if(*t == '\0')
            end = TRUE;
        if(end)
            *s++ = '\0';
        else
            *s++ = *t++;
    }
    return start;
}

int strcmp(char *s, char *t, int n) {
    int i = 0;
    int end = FALSE;
    
    for(; *s == *t && i++ < n; s++, t++)
        if(*s == '\0')
            return 0;
    if(i >= n)
        return 0;

    return *s - *t;
}
