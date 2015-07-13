// print the arbitrary longest line and its longest line
#include <stdio.h>
#define MAX 1000
#define TRUE 1
#define FALSE 0
#define SIZE 100000
int get(char line[], int maxline);
void copy(char from[], char to[]);
void concat(char result[], char first[], char second[]);
void clear(char string[]);

main(){
    char longest[SIZE], string[MAX], chunk[MAX], accum[SIZE]="";

    int maxlength = 0, length, next=0, acc=0, larger;
    larger = FALSE;
    while((length = get(string, MAX)) != 0){
        acc += length;
        concat(accum, accum, string);
        while(length == MAX-1 && string[MAX-2] != '\n'){
            next = get(string, MAX);
            acc += next;
            concat(accum, accum, string);
            if(acc > maxlength){
                maxlength = acc;
                copy(accum, longest);
                larger = TRUE;
            }
            length =  next;
        }
        acc = 0;
        clear(accum);
        if(length > maxlength && !larger){
            maxlength = length;
            copy(string, longest);
        }
    }
    
    if(maxlength > 0)
        printf("\nThe longest line is :\n%s", longest);
    printf("\nThe length of the longest line is: %d\n", maxlength);
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
