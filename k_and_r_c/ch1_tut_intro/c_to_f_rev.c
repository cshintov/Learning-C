// prints the conversion table from celcius to fahrenheit 

#include <stdio.h>
#define UPPER 300
#define LOWER 0
#define STEP 20

main(){
    float celcius;

    printf("%s\t%s", "Celcius", "Fahrenheit\n");
    for(celcius = UPPER; celcius >= LOWER; celcius -= STEP){
        //celcius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%7.0f\t%10.2f\n", celcius, (9.0 / 5.0) * celcius + 32.0);
    }
}
