// removes comments from a c program 
#include <stdio.h>
#define MAX 1000
#define TRUE 1
#define FALSE 0
#define NOCOMMENT -1
#define SIZE 100000
int get(char line[], int maxline);
void concat(char result[], char first[], char second[]);
int ifcomment(char string[]);
int endcom(char string[], int start);
void delete(char string[], int start, int end);
int trim(char string[], char to[]);
main(){
    char string[MAX]="", accum[SIZE]="", trimmed[MAX]="";
    int start, end=0;
    while((get(string, MAX)) != 0){
        trim(string, trimmed);
        start = ifcomment(string);
        if(start >= 0){
            end = endcom(string, start);
            delete(string, start, end);
            trim(string, trimmed);
        }
        concat(accum, accum, trimmed);
    }
    
    printf("\nThe uncommented program is :\n%s", accum);
    return 0;
}

int ifcomment(char string[]){
    int in = FALSE, i=0, chr;
    int start = NOCOMMENT;
    for(i = 0; (chr = string[i]) != '\0'; i++){
        if(chr == '\"' || chr == '\''){
            if(!in) 
                in = TRUE;
            else
                in = FALSE;
        }
        if(i <= MAX-1 && !in){
            if(chr == '*' && string[i+1] == '/'){
                start = 0;
                break;
            }
            if(chr == '/' && string[i+1] == '/'){
                start = i;
                break;
            }
            if(chr == '/' && string[i+1] == '*'){
                start = i;
                break;
            }
        }
    }
    return start;
}

int endcom(char string[], int start){
    int i=0, chr, end = 0;
    for(i = start; (chr = string[i]) != '\0'; i++){
        if(i <= MAX-1){
            if(chr == '*' && string[i+1] == '/'){
                end = i+1;
                break;
            }
        }
    }
    if(!end)
        end = i-1;
    return end;
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

void delete(char string[], int start, int end){
    int i,j;
    if(string[end+2] == '\0')
        string[start] = '\0';
    else{
        for(j=0,i=end+1; string[i] != '\0'; i++,j++){
            string[j] = string[i];
        }
        string[j] = '\0';
    }
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
