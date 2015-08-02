// checks whether t occurs at the end of s

#include <stdio.h>
#define TRUE  1
#define FALSE 0
int strend(char *s, char *t);

int main() {
    char s[15] = "aoao";
    char t[15] = "ad";
    if(strend(s, t))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}

int strend(char *s, char *t) {
    int len = 0;
    while(*s != '\0') {
        if(*s == *t) {
            len++;
            t++;
            if(*t == 0)
                t -= len;
        } else {
            t -= len;
            len = 0;
        }
        s++;
    }
    if(len)
        return TRUE;
    else
        return FALSE;
}
