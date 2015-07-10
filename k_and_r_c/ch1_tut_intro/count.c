// counts the number of charactes in the input

#include <stdio.h>

main(){
    double num_char;

    for(num_char = 0; getchar() != EOF; ++num_char);
    printf("\n%.0f\n",num_char);

    num_char = 0;
    while(getchar() != EOF){
        num_char++;
    }
    printf("\n%0.f\n", num_char);
}

