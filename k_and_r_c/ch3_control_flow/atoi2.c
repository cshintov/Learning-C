// converts integer string to integer

#include <stdio.h>
#include <ctype.h>

int atoi2(char str[]);

main() {
    char s[10] = " 123", t[10] = "-234";
    printf(" 123 = %d\n", atoi2(s));
    printf("-234 = %d\n", atoi2(t));
}

int atoi2(char str[]) {
    int i, sign, num;
    sign = 1;
    //skip space
    for(i = 0; isspace(str[i]); i++)
        ;

    //skip sign and store it
    if(str[i] == '+' || str[i] == '-'){
        sign = (str[i] == '+') ? 1 : -1;
        i++;
    }

    for(num = 0;isdigit(str[i]); i++)
        num = 10 * num + (str[i] - '0');

    return num * sign;
}
