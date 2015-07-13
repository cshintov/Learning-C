// print the longest line
#include <stdio.h>
#define MAX 1000
#define TRUE 1
#define FALSE 0
#define SIZE 100000
int get(char line[], int maxline);
void concat(char result[], char first[], char second[]);
void reverse(char string[], char revstr[]);
int strlength(char striing[]);
void clear(char string[]);
main(){
    char string[MAX], accum[SIZE]="",reversed[SIZE];
    int length;

    while((length = get(string, MAX)) != 0){
        reverse(string, reversed);
        concat(accum, accum, reversed);
        clear(reversed);
    }
    
    printf("\nThe output is:\n%s", accum);
    return 0;
}

int strlength(char string[]){
    int i = 0;
    while(string[i] != '\0')
        i++;
    return i;
}
void reverse(char string[], char revstr[]){
    int length, i, j;
    length = strlength(string);
    for(i = 0, j = length-2; j >= 0; i++, j--)
        revstr[i] = string[j];
    revstr[i] ='\n';
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
