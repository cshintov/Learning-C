// reverse polish calculator

#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

#define MAXOP 100

int main() {
    int type;
    double op2;
    char str[MAXOP];

    while((type = getop(str)) != EOF) {
        switch(type) {
            case NUMBER :
                push(atof(str));
                break;

            case '+' :
                push(pop() + pop());
                break;

            case '*' :
                push(pop() * pop());
                break;

            case '-' :
                op2 = pop();
                push(pop() - op2);
                break;
            
            case '/' :
                op2 = pop();
                if(op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("Error: Zero Divisor \n");
                break;

            case '\n':
                printf("answer: %.8g\n", pop());
                break;

            default:
                printf("Error: Unknown Command %s!\n",str);
                break;
        }    
    }

    return 0;
}
