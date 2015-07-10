// print the longest line
#include <stdio.h>
#define MAX 1000

int get(char line[], int maxline);
void copy(char from[], char to[]);

main(){
    char longest[MAX], string[MAX];
    int maxlength = 0, length;
    while((length = get(string, MAX)) != 0){
        if(length > maxlength){
            maxlength = length;
            copy(string, longest);
        }
    }
    
    if(maxlength > 0)
        printf("\nThe longest line is :\n%s", longest);
    return 0;
}

int get(char line[], int lim){
    int i, chr;

    for(i=0; i < lim - 1 && (chr=getchar()) != EOF && chr != '\n'; i++){
        line[i] =  chr;
    }

    if(chr == '\n'){
        line[i] = chr;
        i++;
    }

    line[i] = '\0';

    return i;
}

void copy(char from[], char to[]){
    int i;

    i = 0;
    while((to[i] = from[i]) != '\0')
        i++;
}
