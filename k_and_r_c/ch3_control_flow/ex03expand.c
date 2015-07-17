//exapand a-z  to abc.....xyz 

#include <stdio.h>
#include <ctype.h>

void expand(char str[], char res[]);
void printlist(char list[]);

main() {
    char str[20] = "b-a", result[100]="";
    expand(str, result);
    printf("the expanded string : \n%s\n", result);
}

void expand(char str[], char res[]) {
    int ndash = 0, i, j, chr;
    char limits[30];
    for(i = 0; str[i]!= '\0'; i++)
        if(str[i] == '-')
            ndash++;
    i = 0;
    if(str[i] == '-') {
        res[i] = '-';
        i++;
    }
    chr = i;
    for(j = 0; (isalnum(str[i])|| str[i] == '-') && str[i+1] != '\0'; i++) {
        if(str[i] == '-') {
            limits[j++] = str[i - 1];
            limits[j++] = str[i + 1];
        }
    }
    //printlist(limits);
    //printf("\n");
    i = chr;
    for(j = 0; isalnum(limits[j]); j += 2) {
        chr =  limits[j];
        while(chr <= limits[j+1]) {
            if(chr != res[i-1])
                res[i++] = chr++;
            else
                chr++;
        }
    }
}

void printlist(char list[]){
    int i;
    printf("The list : ");
    for(i=0; isalnum(list[i]); i++)
        printf("%c ",list[i]);
}
