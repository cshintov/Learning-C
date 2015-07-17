// convert a number to its string representation

#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char str[]);
void itoa(int n, char str[], int min);

main() {
    char num[50] = "";
    int n;
    n = -125;
    itoa(n, num, 5);
    printf("%s\n", num);
}

void itoa(int num, char  str[], int size) {
    int i, sign, blnk;
    unsigned number;
    i = 0;
    if(num < 0) {
        number = -num;
        sign = -1;
    }
    else
        number = num;
        
    do {
        str[i++] = number % 10 + '0';
    } while((number /= 10) > 0);

    if(sign < 0)
        str[i++] = '-';

    blnk = size - strlen(str);
    printf("%d num of blnks needed\n",blnk);
    if(blnk > 0)
        for(sign = 0; sign < blnk; sign++)
            str[i++] = ' ';
    
    reverse(str);
}

void reverse(char str[]) {
    int i, j, chr;
    
    for(i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        chr = str[i];
        str[i] = str[j];
        str[j] = chr;
    }
}
