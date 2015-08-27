/*
 elementary python virtual machine  with arithmetic, logical operations
 and if-else statement, and while loop 
*/

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
            case 0x64: 
                load_const(cur);
                cur += 2;
                break;

            case 0x65: 
                load_name(cur);
                cur += 2;
                break;

            case 0x5a:
                store_name(cur);
                cur += 2;
                break;
                
            case 0x47:
                print_item();
                cur += 1;
                break;
            
            case 0x6b:
                compare_op(cur);
                cur += 2;
                break;
                
            case 0x48:
                print_newline();
                cur += 1;
                break;

            case 0x17:
                binary_add();
                cur += 1;
                break;

            case 0x14:
                binary_multiply();
                cur += 1;
                break;

            case 0x15:
                binary_divide();
                cur += 1;
                break;

            case 0x18:
                binary_subtract();
                cur += 1;
                break;

            case 0x16:
                binary_modulo();
                cur += 1;
                break;
            
            case 0x72:
                cur = pop_jump_if_false(cur);
                break;
            
            case 0x73:
                cur = pop_jump_if_true(cur);
                break;
            
            case 0x6e:
                cur = jump_forward(cur);
                break;
            
            case 0x71:
                cur = jump_absolute(cur);
                break;

            case 0x78:
                cur += 2;
                break;

            case 0x57:
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
    //test();    
    return 0;
}

