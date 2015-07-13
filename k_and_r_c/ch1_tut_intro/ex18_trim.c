// print lines after trimming trailing blanks and tabs and avoids entire blank lines
#include <stdio.h>
#define MAX 1000
#define TRUE 1
#define FALSE 0
#define SIZE 100000

int get(char line[], int maxline);
void concat(char result[], char first[], char second[]);
int trim(char string[], char to[]);
main(){
    char string[MAX], accum[SIZE]="", trimmed[MAX];
    int length, trim_length ;

    while((length = get(string, MAX)) != 0){
        trim_length = trim(string, trimmed);
        if(trim_length)
            concat(accum, accum, trimmed);
        while(length == MAX-1 && string[MAX-2] != '\n'){
            length = get(string, MAX);
            concat(accum, accum, string);
        }
    }
    trim(accum, trimmed);
    printf("\nThe modified input :\n%s", accum);
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

void concat(char result[], char first[], char second[]){
    int i, j;
    for(i=0; first[i] != '\0'; i++)
        result[i] = first[i];

    for(j=0; second[j] != '\0'; j++){
        result[i] = second[j];
        i++;
    }
    result[i] = '\0';
}

int trim(char string[], char to[]){
    int begin = FALSE, i, j = 0;
    char chr, end = 0;
    to[0] = '\n'; to[1] = '\0';
    if(string[0] == '\n')
        return FALSE;
    for(i=0; (chr = string[i]) != '\0'; i++){
        if(chr != ' ' && chr != '\t'){
            begin = TRUE;
            end = 0;
        }
        else if(!end){
            end = i;
        }
        if(begin){
            to[j] = string[i];
            j++;
        }
    }
    to[j] = '\0';
    if(end){
        to[end] =  '\n';
        to[end+1] = '\0';
    }
    return TRUE;
}
