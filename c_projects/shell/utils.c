#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include "utils.h"

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

void print_argv(char** argv, int n)
{
    while(n--)
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
    *cur = '\0';
    return reds;
}

int which_redir(char* c) 
{
    if (c == NULL)
        return NONE;
    if (*c == '<')
        return IN_RED;
    else if (*c == '>')
        return OUT_RED;
    else if (*c == '|')
        return PIPE;
    return NONE;
}

int find_redir(char** argv)
{
    int idx = 0;
    while(argv[idx] != NULL) {
        if (which_redir(argv[idx]) != NONE)
            return idx;
        idx++;
    }
    return idx;
}


void setup_input_red(char* file)
{
    int fd;
    if((fd = open(file, O_RDONLY, 0644)) < 0) {
        printf("error:couldn't open %s", file);
        exit(EXIT_FAILURE);
    } else {
        dup2(fd, 0);
    }
}

void setup_output_red(char* file)
{
    int fd;
    if((fd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
        printf("error:couldn't open %s", file);
        exit(EXIT_FAILURE);
    } else {
        close(1);
        dup2(fd, 1);
    }
}

void setup_redir(char** argv, int idx)
{
    int type = which_redir(argv[idx]);
    if (type == IN_RED)
        setup_input_red(argv[idx+1]);
    else if (type == OUT_RED)
        setup_output_red(argv[idx+1]);
}


char** get_comm(char** argv)
{
    char** targv = malloc(sizeof targv * MAXSIZE);
    int i = 0;
    while(*argv != NULL) {
        if (**argv == IN_RED || **argv == OUT_RED)
            argv += 2;
        else
            targv[i++] = *(argv++);
    }
    targv[i] = NULL;
    return targv;
}
