// reverse polish calculator with modulus and negative numbers

#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'
#define MAXOP 100

int getop(char str[]);
void push(double item);
double pop(void);

main() {
    int type, i, var;
    double op2, ans = 0.0;
    char str[MAXOP];
    int vars[26];

    for(i=0; i<26; i++)
        vars[i] == 0;

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
            
            case '=':
                pop();
                op2 = pop();
                push(op2);
                if (var - 'a' < 26)
                    vars[var - 'a'] = op2;
                break;

            case 'v':
                var = str[0];
                push(vars[var - 'a']);
                break;
                
            case '\n':
                ans = pop();
                printf("answer: %.8g\n", ans);
                break;

            default:
                if(str[0] == 'A')
                    push(ans);
                else 
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

int getop(char str[]) {
    int i, c;
    i = 0;
    while((str[0] = c = getch()) == ' ' || c == '\t')
        ;
    str[1] = '\0';
    
    if(!isdigit(c) && c != '.')
        if( c == '-' && isdigit(str[1] = getch())){
            i = 1;
            c = str[1];
        } else {
            if(str[1] == '\n')
                ungetch(str[1]);
            if(c >= 'a' && c<= 'z')
                return 'v';
            return c;
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

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();   
}

void ungetch(int c) {
    if(bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch : Too many values!\n");
}
