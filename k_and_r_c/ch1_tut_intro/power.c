// implements power(m,n) , returns m raised to n where n is positive

#include <stdio.h>

int power(int m, int n);

main(){
    int i;

    for(i = 0; i < 10; i++)
        printf("%d %d %d\n", i, power(2, i), power(-3, i));
}

int power(int base, int n){
    int prod, i;
    prod = 1;

    if(n <= 0)
        return 1;

    for(i = 0; i < n; i++)
        prod *= base;

    return prod;
}
