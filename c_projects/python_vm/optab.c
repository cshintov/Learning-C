
/* creates the opcode : opname table as a binary search tree */

#include "utils.h"
#include <stdio.h>

FILE* open_file(char *fname)
{
    FILE *fp;
    if((fp = fopen(fname, "r")) == NULL)
        printf("Error: could not open file!");
    return fp;
}


struct node* create_optab(char* filename)
{
    FILE *optxt;
    unsigned int opcode;
    char opname[20] = "";
    char str[50] = "";
    struct node* optab = NULL;
    optxt = open_file(filename);
    while(fgets(str, sizeof(str), optxt) != NULL){
        sscanf(str, "%s %x", opname, &opcode);
        optab = insert(optab, opcode, opname);
    }

    return optab;
}

char* get_opname(struct node* optab, unsigned int opcode)
{
    return lookup(optab, opcode);
}

