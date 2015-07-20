// reverse polish calculator with sin, exp and pow

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER '0'
#define MAXOP 100

int getop(char str[]);
void push(double item);
double pop(void);

main() {
    int type;
    double op2, op1;
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

            case '%' :
                op2 = pop();
                if(op2 != 0.0)
                    push((int)pop() % (int)op2);
                else
                    printf("Error: Zero Divisor \n");
                break;
            
            case 's' :
                op2 = pop();
                push(sin(op2));
                break;
            
            case 'e' :
                op2 = pop();
                push(exp(op2));
                break;

            case 'p' :
                op1 = pop();
                op2 = pop();
                push(pow(op2,op1));
                break;
            case '\n':
                printf("answer: %.8g\n", pop());
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

int getch(void);
void ungetch(int);
int func(int);

int getop(char str[]) {
    int i, c;
    i = 0;
    while((str[0] = c = getch()) == ' ' || c == '\t')
        ;
    str[1] = '\0';
    
    if(!isdigit(c) && c != '.'){
        if(c == '-' && isdigit(str[1] = getch())){ //checking for negative numbers
            i = 1;
            c = str[1];
        } else {
            if(str[1] == '\n')
                ungetch(str[1]);
            str[1] = '\0';
            if(c == func(c))
                return c;
            return c;
        }
    }
    if(isdigit(c))
        while(isdigit(str[++i] = c = getch()))
            ;

    if(c == '.')
        while(isdigit(str[++i] = c = getch()))
            ;

    str[i] = '\0';
    if(c != EOF)
        ungetch(c);

    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch() {
    return (bufp > 0) ? buf[--bufp] : getchar();   
}

void ungetch(int c) {
    if(bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch : Too many values!\n");
}

int func(int c) {
    int n;
    if(c == 's' && getch() == 'i' && getch() == 'n'){
        return c;
    }
    if(c == 'e' && getch() == 'x' && getch() == 'p'){
        return c;
    }
    if(c == 'p' && getch() == 'o' && getch() == 'w'){
        return c;
    }
    return 'u';
}
