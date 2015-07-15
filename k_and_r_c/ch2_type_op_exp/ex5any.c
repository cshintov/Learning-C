// finds the first location in a string at which any character from another string occurs else returns -1

#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define NOTPRESENT -1
int any(char str[], char strg[]);
int ispresent (int chr, char str[]);


main() {
    char str[] = "shiihio";
    
    printf("first common letter position: %d\n", any(str,"tn"));
}


int any(char str[], char strg[]) {
    int i;

    for(i = 0; str[i] != '\0'; i++)
        if(ispresent(str[i], strg))
            return i;

    return NOTPRESENT;
}


int ispresent(int chr, char str[]) {
    int i;

    for(i = 0; str[i] != '\0'; i++) 
        if(str[i] == chr)
            return TRUE;

    return FALSE;
}
