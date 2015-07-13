// print all lines of length greater than 80 characters.
#include <stdio.h>
#define MAX 1000
#define TRUE 1
#define FALSE 0
#define SIZE 100000
int get(char line[], int maxline);
void concat(char result[], char first[], char second[]);

main(){
    char string[MAX], accum[SIZE]="";
    int length, larger;
    larger = FALSE;

    while((length = get(string, MAX)) != 0){
        if(length > 80)
            concat(accum, accum, string);
        while(length == MAX-1 && string[MAX-2] != '\n'){
            length = get(string, MAX);
            concat(accum, accum, string);
        }
    }
    
    printf("\nThe longest line is :\n%s", accum);
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

void concat(char result[], char first[], char second[]){
    int i=0;
    while(first[i] != '\0'){
        result[i] = first[i];
        i++;
    }
    int j=0;
    while(second[j] != '\0'){
        result[i] = second[j];
        j++;
        i++;
    }
    result[i] = '\0';
}

void clear(char string[]){
    int i;
    i = 0;
    while(string[i] != '\0'){
        string[i] = '\0';
        i++;
    }
}
