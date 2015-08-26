/* reads the binary .pyc file */
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1
#define NUM 4
#define HAVE_ARG 90
#define MAXPYC 5000
struct node* optab;

FILE* open_read(char *filename)
{
    FILE* fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("\n***error occured while opening file***\n");
        exit(1);
    }
    return fp;
}


int read(char* buf, FILE* fp)
{
    if(SIZE * NUM != fread(buf, SIZE, NUM, fp)) {
        return FALSE;
    }
    return TRUE;
}


int read_pyc(char *fname, unsigned* pycbuf)
{
    FILE* fp;
    unsigned char buf[100];
    int i, j = 0;
    memset(buf, 0, sizeof(buf));

    fp = open_read(fname);
    while(read(buf, fp)) { 
        for(i = 0; i < 4; i++)
            if(j < MAXPYC) {
                pycbuf[j++] = buf[i];
            } else {
                printf("Too large file!");
                exit(1);
            }
    }
    return j; /* size of the pycfile */
}

int have_arg(unsigned opcode)
{
    if (opcode < HAVE_ARG)
        return FALSE;
    else
        return TRUE;
}


int find_start(unsigned* pycbuf, int size)
{
    int i;
    for(i = 0; pycbuf[i] != 0x73; i++)
        ;
    return i+5; /* the start of the code */
}

/* checks whether cur points to a callable definition 
 * currently implemented only for functions 
 */
int callable(int cur, unsigned* pycbuf)
{
    if (pycbuf[cur] == 0x64 && pycbuf[cur+3] == 0x84)
        return TRUE;
    else
        return FALSE;
}


int get_op_arg(unsigned* pycbuf, int cur)
{
    int l = pycbuf[cur+1];
    int m = pycbuf[cur+2];
    return l | m << 8; /* l + m * 256 */
}

int end(unsigned* pycbuf, int cur)
{
    if (pycbuf[cur] == 0x64 && pycbuf[cur+3] == 0x53)
        return TRUE;
    else
        return FALSE;
}

int end_callable(unsigned* pycbuf, int cur)
{
    if (pycbuf[cur] == 0x53)
        return TRUE;
    else
        return FALSE;
}


int find_start_callable(unsigned* pycbuf, int dealt)
{
    int i;
    for(i = dealt; pycbuf[i] != 0x43; i++)
        ;
    return i+9; /* the start of the code */
}

int dis_callable(unsigned* pycbuf, int dealt, int size)
{
    printf("\n");
    int start = find_start_callable(pycbuf, dealt);
    int cur = start;
    while (!end_callable(pycbuf, cur) && !(cur >= size)) {
        if(!(callable(cur, pycbuf))) {
            printf("%s", get_opname(optab, pycbuf[cur]));
            if (have_arg(pycbuf[cur])) {
                printf(" : %d\n", get_op_arg(pycbuf, cur));
                cur += 3;
            } else {
                printf("\n");
                cur += 1; /* no argument opcode */
            }
        } else {
            dealt = dis_callable(pycbuf, cur, size);
            cur += 9; /* opcode after funtion definition */
        }
    }
    printf("%s\n\n", get_opname(optab, pycbuf[cur]));
    return cur;
}


void print_assembly(unsigned* pycbuf, int cur, int size)
{
    int dealt = cur;
    while (!end(pycbuf, cur) && !(cur >= size)) {
        if(!(callable(cur, pycbuf))) {
            printf("%s", get_opname(optab, pycbuf[cur]));
            if (have_arg(pycbuf[cur])) {
                printf(" : %d\n", get_op_arg(pycbuf, cur));
                cur += 3;
            } else {
                printf("\n");
                cur += 1; /* no argument opcode */
            }
        } else {
            dealt = dis_callable(pycbuf, dealt, size);
            cur += 9; /* opcode after funtion definition */
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
    cur = find_start(pycbuf, size); /* find start of the code */
    printf("\n");    
    print_assembly(pycbuf, cur, size);
    printf("\n");    

    return 0;
}
