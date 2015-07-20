//converts floating point string to floating point number

#include <stdio.h>
#include <string.h>

double atof(char str[]);

main() {
    char num[] = "-2.3e-2";
    printf("-2.3e-2 is the number %10.8f\n", atof(num));
    printf(" -3.6 is the number %10.8f\n", atof(" -3.6"));
}

double atof(char str[]) {
    int i, sign, expsign;
    double val, power;
    for(i=0; isspace(str[i]); i++)
        ;
    sign = (str[i] == '-') ? -1 : 1;
    if(str[i] == '+' || str[i] == '-')
        i++;

    val = 0;
    while(isdigit(str[i]))
        val = val * 10.0 + (str[i++] - '0');
    
    if(str[i] == '.')
        i++;

    for(power=1.0; isdigit(str[i]); i++) {
        val = val * 10.0 + (str[i] - '0');
        power *= 10;
    }

    if(str[i] == 'e' || str[i] == 'E') {
        i++;

        expsign = (str[i] == '-') ? -1 : 1;
        if(str[i] == '+' || str[i] == '-')
            i++;
    
        int exp;
        for(exp = 0; isdigit(str[i]); i++)
            exp = exp * 10.0 + (str[i] - '0');
    
        if(expsign < 0) {
            for(i=0; i<exp; i++)
                val /= 10.0;
        } else {
            for(i=0; i<exp; i++)
                val *= 10.0;
        }
    }
    return sign * val / power;
}
/*
double atof(char str[]) {
    int i, sign;
    double val, power;
    for(i=0; isspace(str[i]); i++)
        ;
    sign = (str[i] == '-') ? -1 : 1;
    if(str[i] == '+' || str[i] == '-')
        i++;

    val = 0;
    while(isdigit(str[i]))
        val = val * 10.0 + (str[i++] - '0');
    
    if(str[i] == '.')
        i++;

    for(power=1.0; isdigit(str[i]); i++){
        val = val * 10.0 + (str[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}*/
