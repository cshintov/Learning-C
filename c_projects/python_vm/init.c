/* initializing data structures */
#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <string.h>

extern struct node* optab;
extern struct field names; 
extern struct field consts;
extern struct field code; 

void field_add(struct field* pycfield, int data)
{
    int length = pycfield->length;
    if (length < MAXVAL)
        pycfield->val[length++] = data;
    else
        printf("error: field full, can't add %d\n", data);
    pycfield->length++;
}

void print_field(struct field pycfield)
{
    int i;
    printf("length: %d\n", pycfield.length);
    for(i = 0; i < pycfield.length; i++)
        printf("%x ", pycfield.val[i]);
    printf("\n");
}

int get_element(struct field* pycfield, int idx)
{
    if (idx >= pycfield->length)
        printf("error get: idx > size\n");
    else
        return pycfield->val[idx];
}

void set_element(struct field* pycfield, int idx, int data)
{
    if (idx >= pycfield->length)
        printf("error set: idx > size\n");
    else
        pycfield->val[idx] = data;    
}

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
    return j;  
}

int have_arg(unsigned opcode)
{
    if (opcode < HAVE_ARG)
        return FALSE;
    else
        return TRUE;
}


int find_start(unsigned* pycbuf)
{
    int i;
    for(i = 0; pycbuf[i] != 0x73; i++)
        ;
    return i+5;
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

int compute_offset(unsigned* pycbuf, int cur, int target)
{
    int start = find_start(pycbuf);
    int end = start + target;
    int offset = 0;
    int opcode = pycbuf[cur];
    if (opcode == 0x6e)
        end = cur + 3 + target;
    else
        cur = start;
    while(cur < end) {
        if(have_arg(pycbuf[cur])) {
            offset += 2;
            cur += 3;
        } else {
            offset += 1;
            cur += 1;
        }
    }
    return offset;
}

int get_op_arg(unsigned* pycbuf, int cur)
{
    int l = pycbuf[cur+1];
    int m = pycbuf[cur+2];
    int oparg = l | m << 8; 
    int opcode = pycbuf[cur];
    if (opcode >= 0x6e && opcode <= 0x73)
        oparg = compute_offset(pycbuf, cur, oparg);
    return oparg;
}

int end(unsigned* pycbuf, int cur)
{
    if (pycbuf[cur] == 0x64 && pycbuf[cur+3] == 0x53)
        return TRUE;
    else
        return FALSE;
}


int find_start_callable(unsigned* pycbuf, int dealt)
{
    int i;
    for(i = dealt; pycbuf[i] != 0x43; i++)
        ;
    return i+9;  
}


int get_code(unsigned* pycbuf, int cur, int size)
{
    int op_arg = 0;
    while (!end(pycbuf, cur) && !(cur >= size)) {
        if(!(callable(cur, pycbuf))) {
            field_add(&code, pycbuf[cur]);
            if (have_arg(pycbuf[cur])) {
                op_arg = get_op_arg(pycbuf, cur);
                field_add(&code, op_arg);
                cur += 3;
            } else {
                cur += 1; 
            }
        } else {
            printf("err:code for callables not implemented\n");
            cur += 9; 
        }
    }
    return cur + 9; 
}

int compute_const(unsigned* pycbuf, int cur)
{
    int i1 = pycbuf[cur+1];
    int i2 = pycbuf[cur+2];
    int i3 = pycbuf[cur+3];
    int i4 = pycbuf[cur+4];
    return i1 | i2 << 8 | i3 << 16 | i4 << 24; 
}

int get_consts(unsigned* pycbuf, int cur, int size)
{
    while(pycbuf[cur] != 0x28 && !(cur >= size)) {
        if(pycbuf[cur] == 0x69) { 
            field_add(&consts, compute_const(pycbuf, cur));
            cur += 5;
        }
        else {
            field_add(&consts, 0);
            cur += 1;
        }
    }
    return cur; 
}

int get_names(unsigned* pycbuf, int cur, int size)
{
    names.length = compute_const(pycbuf, cur);
}

void initialize(unsigned* pycbuf, int cur, int size)
{
    cur = get_code(pycbuf, cur, size);
    cur = get_consts(pycbuf, cur, size);
    get_names(pycbuf, cur, size);
}

