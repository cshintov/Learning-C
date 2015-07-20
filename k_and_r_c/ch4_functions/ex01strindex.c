// find the rightmost index of the substring in a string

#include <stdio.h>

int strindex1(char str[], char sub[]);
int strindex2(char str[], char sub[]);

main() {
    printf("%d leftmost\n",strindex1("shintoin", ""));
    printf("%d rightmost\n",strindex2("shintoin", ""));
}

int strindex1(char str[], char sub[]) {
    int i, j, k;

    for(i=0; str[i]!='\0'; i++) {
        for(j=i, k=0; sub[k]!='\0' && str[j]==sub[k];k++, j++)
            ;
        if(sub[k] == '\0' && k > 0)
            return i;
    }
    return -1;
}

int strindex2(char str[], char sub[]) {
    int i, j, k, index;

    index = -1;
    for(i=0; str[i]!='\0'; i++) {
        for(j=i, k=0; sub[k]!='\0' && str[j]==sub[k];k++, j++)
            ;
        if(sub[k] == '\0' && k > 0)
            index = i;
    }
    return index;
}
