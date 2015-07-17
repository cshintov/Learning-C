// convert a number to its string representation

#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char str[]);
void itoa(int n, char str[]);

main() {
    char num[50] = "";
    int n;
    n = INT_MIN;
    itoa(n, num);
    printf("%s\n", num);
}

void itoa(int num, char  str[]) {
    int i, sign;
    unsigned number;
    i = 0;
    if(num < 0) {
        number = -num;
        sign = -1;
    }
        
    do {
        str[i++] = number % 10 + '0';
    } while((number /= 10) > 0);

    if(sign < 0)
        str[i++] = '-';
    reverse(str);
    str[i] = '\0';   
}

void reverse(char str[]) {
    int i, j, chr;
    
    for(i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        chr = str[i];
        str[i] = str[j];
        str[j] = chr;
    }
}
