/*
 elementary python virtual machine  with arithmetic, logical operations
 and if-else statement, and while loop 
*/
#include "opcodes.h"
#include "pyvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int obj_cnt;
void execute(struct code_obj* pobj) {
    int cur = 0;
    int opcode = 0;
    struct code_obj* pfun;
    while (cur < (pobj->code).length) {
        opcode = get_element(&(pobj->code), cur);
        switch(opcode) {
            case LOAD_CONSTANT: 
                load_const(pobj, cur);
                cur += 2;
                break;

            case LOAD_NAME: 
                load_name(pobj, cur);
                cur += 2;
                break;

            case LOAD_GLOBAL: 
                load_global(pobj, cur);
                cur += 2;
                break;

            case STORE_NAME:
                store_name(pobj, cur);
                cur += 2;
                break;
                
            case PRINT_ITEM:
                print_item();
                cur += 1;
                break;
            
            case PRINT_NEWLINE:
                print_newline();
                cur += 1;
                break;

            case COMPARE_OP:
                compare_op(pobj, cur);
                cur += 2;
                break;
                
            case BINARY_ADD:
                binary_add();
                cur += 1;
                break;

            case BINARY_MULTIPLY:
                binary_multiply();
                cur += 1;
                break;

            case BINARY_DIVIDE:
                binary_divide();
                cur += 1;
                break;

            case BINARY_SUBTRACT:
                binary_subtract();
                cur += 1;
                break;

            case BINARY_MODULO:
                binary_modulo();
                cur += 1;
                break;
            
            case POP_JUMP_IF_FALSE:
                cur = pop_jump_if_false(pobj, cur);
                break;
            
            case POP_JUMP_IF_TRUE:
                cur = pop_jump_if_true(pobj, cur);
                break;
            
            case JUMP_FORWARD:
                cur = jump_forward(pobj, cur);
                break;
            
            case JUMP_ABSOLUTE:
                cur = jump_absolute(pobj, cur);
                break;

            case SETUP_LOOP:
                cur += 2;
                break;

            case POP_BLOCK:
                cur += 1;
                break;
            
            case UNARY_NOT:
                unary_not();
                cur += 1;
                break;
            
            case CALL_FUNCTION:
                call_function(pobj, cur);
                cur += 2;
                break;

            case LOAD_FAST:
                load_fast(pobj, cur);
                cur += 2;
                break;
            
            case STORE_FAST:
                store_fast(pobj, cur);
                cur += 2;
                break;
            
            case POP_TOP:
                pop_top();
                cur += 1;
                break;

            case RETURN_VALUE:
                return;

            default:
                printf("error: unknown opcode: %x!\n", opcode);
                return;
        }
    }
}


int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("usage ./dis pycfile!\n");
        exit(1);
    }
    
    char* pycfile = argv[1];
    unsigned pycbuf[MAXPYC] = {0};
    int start, size;
    struct code_obj* pcode_o = malloc(sizeof *pcode_o);
    
    /* read pyc file into pycbuf integer array */
    size = read_pyc(pycfile, pycbuf);
    
    /* find start of the code */
    start = find_start(pycbuf, 0);
    //printf("%c start of the code %d\n", pycbuf[start], start);
    
    /* getting the co_code, co_consts and co_names */
    int namei = get_fields(pycbuf, pcode_o, start, size);
    //printf("the name of the code obj is :%s\n", objects[namei]->name);

    printf("\nStarting Execution\n\n");    
    execute(pcode_o);    
    printf("\nEnd of execution!\n");
    return 0;
}

