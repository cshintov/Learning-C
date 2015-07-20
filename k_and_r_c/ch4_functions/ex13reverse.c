// recursive inplace string-reverse

#include <stdio.h>
#include <string.h>

void reverse(char str[]);

int main() {
    char str[100] = "shinto";
    
    reverse(str);
    printf("The reversed string: %s\n", str);

    return 0;
}

void reverse(char str[]){
    void helper(char str[], int end);

    helper(str, strlen(str)-1);
}
void helper(char str[], int end) {
    static int ndx = 0;
    int temp;

    if(ndx < end) {
        temp = str[ndx];
        str[ndx] = str[end];
        str[end] = temp;
        ndx++;
        helper(str, end-1);
    }
}
