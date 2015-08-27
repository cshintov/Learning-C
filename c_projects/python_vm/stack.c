#include <stdio.h>
#define MAXVAL 500
static int stack[MAXVAL] = {0};
static top = 0;
/* push: push onto stack */
void push(int data)
{
    if (top < MAXVAL)
        stack[top++] = data;
    else
        printf("error: stack full, can't push %d\n", data);
}
/* pop: pop and return top stackue from stack */
int pop(void)
{
    if (top > 0)
        return stack[--top];
    else {
        printf("error: stack empty\n");
        getchar();
        return 0;
    }
}


