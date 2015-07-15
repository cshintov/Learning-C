//convert hexadecimal string  to int
#include <stdio.h>

enum hex { SMALL, CAP, DIG, NOTVAL};
int htoi(char s[]);
enum hex isvalid(int chr);

main() {
    char s[] = "4";
    printf(" %s = %d \n", s, htoi(s));
    printf(" %s = %d \n", "kF", htoi("kF"));
    printf(" %s = %d \n", "0xF1", htoi("0xF1"));
}

int htoi(char s[]) {
    int i, num;
    enum hex type;
    num = 0;
    i = 0;
    //skipping optional 0x or 0X
    if(s[i] == '0')
        if(s[i+1] == 'x' || s[i+1] == 'X')
            i = 2;
    for( ; (type = isvalid(s[i])) != NOTVAL; i++) {
        if(type == DIG)
            num = 16 * num + (s[i] - '0');
        else if(type == SMALL)
            num  = 16 * num + (s[i] - 'a' + 10);
        else
            num = 16 * num + (s[i] - 'A' + 10);
    }

    if(type == NOTVAL && s[i] != '\0')
        printf("Not a valid hexadecimal number!\n");
    return num;
}

enum hex isvalid(int chr) {
    enum hex type = NOTVAL;
    if( chr >= '0' && chr <= '9')
        type = DIG;
    else if( chr >= 'a' && chr <= 'f')
        type = SMALL;
    else if( chr >= 'A' && chr <= 'F')
        type = CAP;
    return type;
}
