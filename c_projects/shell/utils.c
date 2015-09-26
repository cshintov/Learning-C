#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include "utils.h"
#include <unistd.h>

void error(char *s)
{
    printf("Error:%s\n",s);
    exit(EXIT_FAILURE);
}
void strip_newline(char *s)
{
    char* pos;
    if((pos = strchr(s, '\n')) != NULL)
        *pos = '\0';
}

char* get_str(char *s, int size)
{
    s = fgets(s, size, stdin);
    if (s != NULL)
        strip_newline(s);
    
    return s;
}

/* find length of the word starting from s */
int find_length(char *s)
{
    char* start = s;
    if (*s == '<' || *s == '>' || *s == '|')
        return 1;
    while(*s != ' ' &&  *s != '\t' && *s != '\0' &&
                *s != '<' && *s != '>' && *s != '|')
        s++;
    return s - start;
}

char* skip_space(char *s)
{
    while(*s == ' ' || *s == '\t')
        s++;
    return s;
}

char** split(char *s)
{
    assert(s != NULL);
    int length, i = 0;
    char *temp;
    char **argv = malloc(MAXSIZE * sizeof argv);
    char *start = skip_space(s);
    while(*start != '\0') {
        length = find_length(start);
        temp = malloc(length+1);
        strncpy(temp, start, length);
        argv[i++] = temp;
        start = skip_space(start + strlen(temp));
    }
    argv[i] = NULL;
    return argv;
}

void print_argv(char** argv)
{
    printf("printing the command list\n");
    while(*argv != NULL)
        printf("%s\n", *(argv++));
}

char** get_argv(char* command)
{
    return split(command);
}

char* get_redirections(char* s)
{
    char* reds  = malloc(REDSIZE);
    char* cur =  reds;
    int in_quot = FALSE;
    *(cur++) = '*';
    while(*s != '\0') {
        
        if (*s == '\'' || *s =='\"')
            if(in_quot)
                in_quot = FALSE;
            else
                in_quot = TRUE;
        
        if(!in_quot && *s == '<' || *s == '>' 
                                || *s == '|') {
            *(cur++) = *s;
        }
        s++;
    
    }
    *(cur++) = '*';
    *cur = '\0';
    return reds;
}

int typeof_redir(char* c) 
{
    if (c == NULL)
        return NONE;
    if (*c == '<')
        return IN_RED;
    else if (*c == '>')
        return OUT_RED;
    else if (*c == '|'){
        return PIPE;
    }
    return NONE;
}

int type(char** argv, int idx)
{
    if (idx == -1)
        return NONE;
    return typeof_redir(argv[idx]);
}

int next_redir(char** argv, int idx)
{
    if (type(argv, idx) != NONE)
        idx++;
    while (argv[idx] != NULL) {
        if (type(argv,idx) != NONE)
            return idx;
        idx++;
    }
    return idx;
}

int prev_redir(char** argv, int idx)
{
    while (idx > 0) {
        if (type(argv, idx-1) != NONE)
            return idx-1;
        idx--;
    }
    if (type(argv, idx) == NONE)
        idx = -1;
    return idx;
}

void get_rw(int* rw, char** argv, int idx)
{
    if (idx == 0)
        rw[0] = idx;
    else 
        rw[0] = prev_redir(argv, idx);
    rw[1] = 1;
    printf("%d read, write %d\n", rw[0], rw[1]);
}

int setup_pipe(int* pfd)
{
    if(pipe(pfd) == -1) {
        printf("Error: pipe\n");
        return FALSE;
    }
    return TRUE;
}


int setup_input_red(char* file)
{
    printf("set in %s\n", file);
    int fd;
    if((fd = open(file, O_RDONLY, 0644)) < 0) {
        printf("error:couldn't open %s", file);
        return FALSE;
    } else {
        if(dup2(fd, 0) == -1)
            error("error dup2 set in\n");;
    }
    return TRUE;
}

int setup_output_red(char* file)
{
    printf("set out %s\n", file);
    int fd;
    if((fd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
        printf("error:couldn't open %s", file);
        return FALSE;
    } else {
        dup2(fd, 1);
    }
    return TRUE;
}

int setup_redir(char** argv, int idx, int* pfd)
{
    int typ = type(argv, idx);
    if (typ == PIPE)
        return setup_pipe(pfd);
    if (typ == IN_RED)
        return setup_input_red(argv[idx+1]);
    else if (typ == OUT_RED)
        return setup_output_red(argv[idx+1]);
    return TRUE;
}


char** get_comm(char** argv, int nxt)
{
    if (argv[nxt] == NULL)
        return argv;
    char redir = *argv[nxt];
    int count = 0;
    char** temp = argv;
    while(*temp != NULL && **(temp++) != redir)
        count++;
    char** comm = malloc(count+1 * sizeof comm);
    temp = comm;
    while(*argv != NULL && **argv != redir)
        *(temp++) = *(argv++);
    *temp = NULL;
    return comm;
}

int mymain(int argc, char** argv)
{
    char s[100];
    printf("%s\n",get_str(s,sizeof(s)));
    argv = get_argv(s);
    int idx = next_redir(argv, 2);
    printf("%d\n", idx);
    get_comm(argv, NONE);
    return 0;
}
