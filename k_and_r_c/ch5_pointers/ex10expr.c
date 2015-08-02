// evaluate reverse polish expressions from commandline
// * should be given in quotes


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER '0'
void push(double);
double pop(void);

int main(int argc, char *argv[]) 
{   
    int type;
    char *str;
    double op2;
    if(argc > 1) {
        while(--argc > 0) {
            if(isdigit(type = (*++argv)[0])) {
                type = NUMBER;
                str = *argv;
            }

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
    
                default:
                    printf("Error: Unknown operator%c!\n",type);
                    break;
            }
        }

        printf("answer: %.8g\n", pop());
    } else
        printf("expr: usage expr rev polish expression\n");
}

#define MAXVAL 100

static double  val[MAXVAL];
static int top = 0;

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
