// prints the conversion table from celcius to fahrenheit 

#include <stdio.h>

main(){
    float fahr, celcius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    celcius = lower;
    printf("%s\t%s", "Celcius", "Fahrenheit\n");
    while(celcius <= upper){
        //celcius = (5.0 / 9.0) * (fahr - 32.0);
        fahr = ((9.0 / 5.0) * celcius) + 32.0; 
        printf("%7.0f\t%10.2f\n", celcius, fahr);
        celcius = celcius + step;
    }
}
