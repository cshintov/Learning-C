//prints the max values possible by each data type

#include <stdio.h>
#include <limits.h>

main() {
    
    printf("%d char min\n", SCHAR_MIN);
    printf("%d char max\n", SCHAR_MAX);
    printf("%d short min\n", SHRT_MIN);
    printf("%d short max\n", SHRT_MAX);
    printf("%d int min\n", INT_MIN);
    printf("%d int max\n", INT_MAX);
    printf("%ld long min\n", LONG_MIN);
    printf("%ld long max\n", LONG_MAX);
    printf("%d unsigned char max\n", UCHAR_MAX);
    printf("%d unsigned short max\n", USHRT_MAX);
    printf("%u unsigned int max\n", UINT_MAX);
    printf("%ld unsigned long max\n", LONG_MAX);

}
