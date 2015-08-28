/*
 elementary python virtual machine  with arithmetic, logical operations
 and if-else statement, and while loop 
*/
#include "opcodes.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node* optab;
struct field names = {{0}, 0};
struct field consts = {{0}, 0};
struct field code = {{0}, 0};

void execute() {
    int cur = 0;
    int opcode = 0;
    while (cur < code.length) {
        opcode = get_element(&code, cur);
        switch(opcode) {
            case LOAD_CONSTANT: 
                load_const(cur);
                cur += 2;
                break;

            case LOAD_NAME: 
                load_name(cur);
                cur += 2;
                break;

            case STORE_NAME:
                store_name(cur);
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
                compare_op(cur);
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
                cur = pop_jump_if_false(cur);
                break;
            
            case POP_JUMP_IF_TRUE:
                cur = pop_jump_if_true(cur);
                break;
            
            case JUMP_FORWARD:
                cur = jump_forward(cur);
                break;
            
            case JUMP_ABSOLUTE:
                cur = jump_absolute(cur);
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
    int cur, size;
    
    /* read pyc file into pycbuf integer array */
    size = read_pyc(pycfile, pycbuf);

    /* constructing the opcode : opname table */
    optab = create_optab("opcodes.txt");
    cur = find_start(pycbuf); /* find start of the code */
    
    /* getting the co_code, co_consts and co_names */
    initialize(pycbuf, cur, size);
    
    printf("\nStarting Execution\n\n");    
    execute();    
    printf("\nEnd of execution!\n");
    return 0;
}

