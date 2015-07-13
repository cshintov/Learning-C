//repalce spaces with equivalent tabs
#include <stdio.h>
#define MAX 1000
#define TAB 8
#define SIZE 100000
int get(char line[], int maxline);
void concat(char result[], char first[], char second[]);
void clear(char string[]);
void entab(char string[], char result[]);
main(){
    char string[MAX]="", accum[SIZE]="", entabed[MAX];
    int length;
    
    while((length = get(string, MAX)) != 0){
        entab(string, entabed);
        concat(accum, accum, entabed);
        clear(entabed);
    }
    
    printf("\nThe output is:\n%s", accum);
    return 0;
}

void entab(char string[], char result[]){
    int i=0, j=0, k=0, temp=0, num =TAB, nc=0;
    int num_t=0, num_blk=0, length=0;
    for(;string[i] != '\0';){
        if(string[i] == ' '){
            for(j=0;string[i] == ' ';j++, i++);
            length = j;
            num_t = length / TAB;
            num_blk = length % TAB;
            for(j = 0; j < num_t; j++, k++)
                result[k] = '\t';
            for(j = 0; j < num_blk; j++, k++)
                result[k] = ' ';
        }
        else{
            result[k] = string[i];
            i++;
            k++;
        }
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
