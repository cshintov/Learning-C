// pointer variants of getline, atoi, itoa, and reverse

#include<string.h>
#include <stdio.h>
#define MAX 10

int mygetline(char *s, int lim);
int atoi(char *s);
void itoa(int num, char *s);
void reverse(char *s);

int main() {
    char s[MAX] = "";
    mygetline(s, MAX);
    printf("The converted number is:%s\n", s);
    return 0;
}

int mygetline(char *s, int lim) {
    printf("here\n");
    char *start = s;
    int chr;
    while(lim-- > 0 && (chr = getchar()) != EOF && chr != '\n')
        *s++ = chr;
    if(chr == '\n')
        *s++ = chr;
    *s = '\0';
    return s - start ;
}

int atoi(char *s) {
    int num = 0;
    while(*s >= '0' && *s <= '9') {
        num = 10 * num + *s - '0';
        s++;
    }
    return num;
}

void itoa(int num, char *s) {
    char *start = s;
    while(num > 0) {
        *s++ =  num % 10 + '0';
        num /= 10;
    }
    reverse(start);
}

void reverse(char *s) {
    char *mid = s + strlen(s)/2;
    char *end = s + strlen(s)-1;
    int temp;
    while(s < mid) {
        temp = *s;
        *s = *end;
        *end = temp;
        end--;
        s++;
    }
}
