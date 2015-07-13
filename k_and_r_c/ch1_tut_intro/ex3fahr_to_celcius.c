// prints the conversion table from fahrenheit to celcius 

#include <stdio.h>

main(){
    float fahr, celcius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    fahr = lower;
    printf("%s\t%s", "Fahrenheit", "Celcius\n");
    while(fahr <= upper){
        celcius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%10.0f\t%7.2f\n", fahr, celcius);
        fahr = fahr + step;
    }
}
