// print the longest line
#include <stdio.h>
#define MAX 1000
#define TAB 8
#define SIZE 100000
int get(char line[], int maxline);
void concat(char result[], char first[], char second[]);
int strlength(char striing[]);
void clear(char string[]);
void detab(char string[], char result[]);
main(){
    char string[MAX], accum[SIZE]="", detabed[MAX];
    int length;

    while((length = get(string, MAX)) != 0){
        detab(string, detabed);
        concat(accum, accum, detabed);
        clear(detabed);
    }
    
    printf("\nThe output is:\n%s", accum);
    return 0;
}

void detab(char string[], char result[]) {
    int i=0, j=0, temp=0, num = TAB;
    int k;
    k = 0;
    while(string[i] != '\0') {
        if(string[i] == '\t') {
            for(j=0; j < num; j++) {
                result[k + j] = ' ';
            }
            k = k + j;
            num = TAB;
        }
        else {
            result[k] = string[i];
            k++;
            num--;
        }
        i++;
    }
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
