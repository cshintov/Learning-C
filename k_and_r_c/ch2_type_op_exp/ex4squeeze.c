// delete charactes from string 1 that matches any character in string 2

#include <stdio.h>

void squeeze(char str[], char delstr[]);
void sqz(char str[], int chr);
main() {
    char str[] = "shiihnito";
    squeeze(str,"hs");
    printf("string afte squeeze: %s\n", str);
}

void squeeze(char str[], char delstr[]) {
    int i;

    for(i = 0; delstr[i] != '\0'; i++)
       sqz(str, delstr[i]);
}

void sqz(char str[], int chr) {
    int i, j;
    for(i = j = 0; str[i] != '\0'; i++) 
        if(str[i] != chr)
            str[j++] = str[i];
    str[j] = '\0';
}
