// prints the conversion table from celcius to fahrenheit 

#include <stdio.h>

float cels_to_fahr(float celcius);

main(){
    float fahr, celcius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    celcius = lower;
    printf("%s\t%s", "Celcius", "Fahrenheit\n");
    while(celcius <= upper){
        fahr = cels_to_fahr(celcius);
        printf("%7.0f\t%10.2f\n", celcius, fahr);
        celcius = celcius + step;
    }
}

float cels_to_fahr(float celcius){
    return ((9.0 / 5.0) * celcius) + 32.0;
}
