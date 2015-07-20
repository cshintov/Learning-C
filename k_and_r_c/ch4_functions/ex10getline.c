// reverse polish calculator with exp, pow, and sin
// using getlin instead of getch and getch

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER '0'
#define MAXOP 100
#define BUFSIZE 100

int getop(char str[]);
void push(double item);
double pop(void);
void getlin(char str[]);
void mathfun(char str[]);

char buf[BUFSIZE];
int bufp = 0;

main() {
    int type;
    double op2, op1;
    char str[MAXOP];
    
    getlin(buf);

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

            case '%' :
                op2 = pop();
                if(op2 != 0.0)
                    push((int)pop() % (int)op2);
                else
                    printf("Error: Zero Divisor \n");
                break;

            case 'm':
                mathfun(str);
                break;

            case '\n':
                printf("answer: %.8g\n", pop());
                getlin(buf);
                break;

            default:
                printf("Error: Unknown Command!\n");
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
}

double pop(void) {
    if(top > 0)
        return val[--top];
    else {
        printf("Error: stack empty!\n");
        return 0.0;
    }
}

#include <ctype.h>

int getop(char str[]) {
    int i, c;
    i = 0;

    while((str[0] = c = buf[bufp++]) == ' ' || c == '\t')
        ;
    str[1] = '\0';
    
//number or operator or math functions or EOF
    if(!isdigit(c) && c != '.' && c != '-') {
        if(isalpha(c)){
            while(isalpha(str[++i] = buf[bufp++]))
                ;
            str[i] = '\0';
            bufp--;
            return 'm';
        }
        return c;
    }

    if(c == '-') {
        if(!isdigit(buf[bufp]))
            return c;
        else
            c = buf[bufp];
    }

    if(isdigit(c))
        while(isdigit(str[++i] = c = buf[bufp++]))
            ;

    if(c == '.')
        while(isdigit(str[++i] = c = buf[bufp++]))
            ;

    bufp--;

    return NUMBER;
}

void getlin(char str[]) {
    int c;
    bufp = 0;
    while((c = getchar()) != '\n')
        str[bufp++] = c;
    str[bufp] = '\n';
    bufp = 0;
}

#include <string.h>

void mathfun(char str[]) {
    double op1;
    if(strcmp("sin", str) == 0) {
        push(sin(pop()));
    } else if(strcmp("exp", str) == 0) {
        push(exp(pop()));
    } else if(strcmp("pow", str) == 0) {
        op1 = pop();
        push(pow(pop(),op1));
    } else {
        printf("Error: \"%s\" Not supported!", str);
    }
}
