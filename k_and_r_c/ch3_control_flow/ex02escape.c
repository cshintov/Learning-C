// replace newline with /n and tab with /t and vice versa

#include <stdio.h>
#define MAX 1000
void escape(char str[], char targ[]);
void rev_escape(char str[], char tar[]);

main() {
    char string[MAX] = "\tfirstline\nsecoondline";
    char target[MAX] = "";

    escape(string, target);
    printf("the string:\n%s\n", string);
    printf("the new string:\n%s\n", target);

    rev_escape(target, string);
    printf("the string:\n%s\n", target);
    printf("the new string:\n%s\n", string);

}

void escape(char strg[], char tar[]) {
    int i, j;
    for(i = j = 0; strg[i] != '\0'; i++){
        switch (strg[i]) {
            case '\n':
                tar[j++] = '\\';
                tar[j++] = 'n';
                break;
            case '\t':
                tar[j++] = '\\';
                tar[j++] = 't';
                break;
            default:
                tar[j++] = strg[i];
                break;
        }
    }
}

//replaces the escape sequence  with real tab or newline
void rev_escape(char str[], char tar[]) {
    int i, j;
    for(i = j = 0; str[i] != '\0'; i++){
        switch (str[i]) {
            case '\\':
                switch(str[++i]) {
                    case 't':
                        tar[j++] = '\t';
                        break;
                    case 'n':
                        tar[j++] = '\n';
                        break;
                    default:
                        tar[j++] = '\\';
                        tar[j++] = str[i];
                        break;
                }
                break;
            default:
                tar[j++] = str[i];
                break;
        }
    }
}
