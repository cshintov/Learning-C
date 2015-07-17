// converts the num to a string representation in the base b

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

void itob(int num, char str[], int base);
void reverse(char str[]);

main() {
    char num[50] = "";
    int n;
    n = 47;
    itob(n, num, 16);
    printf("\nresult %s base %d\n", num, 16);
}

void itob(int num, char  str[], int base) {
    int i, sign, chr;
    i = 0;
    if(num < 0)
        sign = -1;
        
    do {
        chr = abs(num % base);
        if(chr > 9) {
            chr = 'A' + chr - 10;
            str[i++] = chr;
        }
        else
            str[i++] = chr + '0';
    } while((num /= base) != 0);

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
