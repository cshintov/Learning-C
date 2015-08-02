// pointer version of strcat(s,t) which concatenates t to the end of s

#include <stdio.h>

void strcat(char *s, char *t);

int main() {
    char s[15] = "shinto";
    char t[15] = ".c.v";
    strcat(s,t);
    printf("after concat: %s\n", s);
    return 0;
}

void strcat(char *s, char *t) {
    while(*s++)
        ;
    s--;
    while((*s++ = *t++))
        ;
}
