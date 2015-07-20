// reverse polish calculator

#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'
#define MAXOP 100

int getop(char str[]);
void push(double item);
double pop(void);

main() {
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
}


#define MAXVAL 100

double  val[MAXVAL];
int top = 0;

void push(double item) {
    if(top < MAXVAL)
        val[top++] = item;
    else
        printf("Error: stack full, can't push!\n");
    printf("pushed item %f\n", val[top-1]);
}

double pop(void) {
    if(top > 0)
        return val[--top];
    else {
        printf("Error: stack empty!\n");
        return 0.0;
    }
    printf("popped item %f\n",val[top]);
}

#include <ctype.h>

int getop(char str[]) {
    int i, c;
    static int chr = 0;
    
    if(chr == 0)
        c = getchar();
    else {
        c = chr;
        chr = 0;
    }

    while((str[0] = c) == ' ' || c == '\t')
        c = getchar();
    str[1] = '\0';
    
    if(!isdigit(c) && c != '.')
        return c;

    i = 0;
    if(isdigit(c))
        while(isdigit(str[++i] = c = getchar()))
            ;

    if(c == '.')
        while(isdigit(str[++i] = c = getchar()))
            ;

    str[i] = '\0';
    if(c != EOF)
        chr = c;

    return NUMBER;
}
