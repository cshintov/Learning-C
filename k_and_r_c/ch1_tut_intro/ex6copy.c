// copies input to output

#include <stdio.h>

main(){
    int c;
    //verifies the value of the condition
    printf("%d\n",getchar() != EOF);
    //prints the value of the EOF character
    printf("vaule of EOF: %d\n",EOF);
    //prints the input untill EOF
    while((c = getchar()) != EOF)
        putchar(c);
}
