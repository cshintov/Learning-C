/* reads the binary .pyc file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct node* optab;
extern struct field names; 
extern struct field consts;
extern struct field code; 

void load_const(int cur)
{
    int oparg = 0;
    oparg = get_element(&code, cur+1);
    push(get_element(&consts, oparg));
}

void load_name(int cur)
{
    int oparg = 0;
    oparg = get_element(&code, cur+1);
    push(get_element(&names, oparg));
}

void store_name(int cur)
{
    int oparg = 0;
    oparg = get_element(&code, cur+1);
    set_element(&names, oparg, pop());
}

int pop_jump_if_false(int cur)
{
    if(!pop())
        return get_element(&code, cur+1);
    else
        return cur+2;
}

int pop_jump_if_true(int cur)
{
    if(pop())
        return get_element(&code, cur+1);
    else
        return cur+2;
}

int jump_forward(int cur)
{
    return cur + get_element(&code, cur+1);
}

int jump_absolute(int cur)
{
    return get_element(&code, cur+1);
}

void compare_op(int cur)
{
    int oparg = 0;
    int b = pop();
    int a = pop();
    int res = a == b;
    oparg = get_element(&code, cur+1);
    switch(oparg) {
        case 0:
            res = a < b;
            break;
        case 1:
            res = res || a < b;
            break;
        case 2:
            break;
        case 3:
            res = !res;
            break;
        case 4:
            res = a > b;
            break;
        case 5:
            res = res || a > b;
            break;
        default:
            break;
    }
    push(res);
}

void print_item(void)
{
    printf("%d", pop());
}

void print_newline(void)
{
    printf("\n");
}

void binary_add(void)
{
    int first = pop();
    int second = pop();
    push(second + first);
}

void binary_multiply(void)
{
    push(pop() * pop());
}

void binary_divide(void)
{
    int first = pop();
    int sec = pop();
    push(sec / first);
}

void binary_modulo(void)
{
    int first = pop();
    int sec = pop();
    push(sec % first);
}

void binary_subtract(void)
{
    int first = pop();
    int sec = pop();
    push(sec - first);
}
