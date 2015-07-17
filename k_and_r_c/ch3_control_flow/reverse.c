// reverse a string in place

#include <stdio.h>
#include <string.h>

void reverse(char str[]);

main() {
    char str[50] = "shinto";
    reverse(str);
    printf("%s\n", str);
}

void reverse(char str[]) {
    int i, j, chr;
    
    for(i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        chr = str[i];
        str[i] = str[j];
        str[j] = chr;
    }
}
