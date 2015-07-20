// recursive integer to string

#include <stdio.h>

void itoa(int num, char str[]);

int main() {
    char str[100];
    int num = -123;
    
    itoa(num, str);
    printf("The converted string: %s\n", str);

    return 0;
}

void itoa(int num, char str[]) {
    static int ndx = 0;
   
    if(num < 0) {
        num = -num;
        str[ndx++] = '-';
    }

    if((num / 10) > 0)
        itoa(num / 10 , str);
    
    str[ndx++] = num % 10 + '0';
    str[ndx] = '\0';
}
