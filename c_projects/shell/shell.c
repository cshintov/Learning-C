#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include <errno.h>

/* argv: list of strings of the entire combination of commands
   redirections: string of all the redirections involved
*/
void execute_redir(char** argv, char* redirections)
{
    int nxt;
    int pid;
    int typ;
    int err;
    int pips[2][2] = {{0,0}, {0,0}};
    int pip_read = FALSE;
    int pip_write = FALSE;
    int nxtpp = 1;
    int prvpp = 0;
    char** comm;

    /* backup standard input and output */
    int std_in = dup(0);
    int std_out = dup(1);

    nxt = next_redir(argv, 0);
    while(*argv != NULL || argv[nxt] != NULL) {
        setup_redir(argv, nxt, pips[!nxtpp]);
        comm = get_comm(argv, nxt);
        if (argv[nxt] != NULL && *argv[nxt] == IN_RED) { /* setup write */
            argv += nxt;
            nxt = next_redir(argv, 1);
            setup_redir(argv, nxt, pips[!nxtpp]);
        }
        nxtpp = !nxtpp;
        typ = type(argv, nxt);
        if (typ == PIPE) /* setup pipe write */
            pip_write = TRUE;

        switch (pid = fork()) {

        case -1:
            error("fork");

        case 0:
            if (pip_read) {   /* set read from pipe */
                if (pips[prvpp][0] != STDIN_FILENO) {
                    if (dup2(pips[prvpp][0], STDIN_FILENO) == -1)
                        error("dup2 2");
                    if (close(pips[prvpp][0]) == -1)
                        error("close 4");
                }
            }
            if (typ == PIPE && pip_write) {  /* setup pipe write */
                if (close(pips[nxtpp][0]) == -1)
                    error("closing read end of writer");
                if (pips[nxtpp][1] != STDOUT_FILENO) {
                    if (dup2(pips[nxtpp][1], STDOUT_FILENO) == -1)
                        error("dup2 1");
                    if (close(pips[nxtpp][1]) == -1)
                        error("close 2");
                }
            }
            err = execvp(comm[0], comm);
            printf("%s: command not found!\n", comm[0]);
            if(err == -1)
                _exit(EXIT_FAILURE);
            _exit(EXIT_SUCCESS);
        
        default:
            wait(NULL);
            if (pip_read == TRUE) {
                pip_read = FALSE;
                if (close(pips[prvpp][0]) == -1)
                    error("parent close read end");
            }
            if (pip_write == TRUE) {
                pip_write = FALSE;
                if (close(pips[nxtpp][1]) == -1)
                    error("parent close write end");
                pip_read = TRUE;
            }
            break;
        }
        
        
        if (argv[nxt] == NULL) {
            break;
        }
        typ = type(argv, nxt);
        if (typ == PIPE) {
            argv += nxt+1;
            prvpp = nxtpp; /* next process read from current pipe */
        } else if (typ == IN_RED || typ ==  OUT_RED)
            argv += nxt + 2;
        nxt = next_redir(argv, 0);
    }
    /*restore standard  input and output */
    dup2(std_in, 0);
    dup2(std_out, 1);
}


void shell(const char *prompt)
{
    char command[100];
    char** argv;
    char* redirections;
    int err = 0; 

    printf("%s", prompt);
    while(get_str(command, sizeof command) != NULL) {
        argv = get_argv(command); /* gets them as a list of strings */
        redirections = get_redirections(command);

        if(argv[0] == NULL) { /* empty command */
            printf("\n%s", prompt);
            continue;
        }

        if(strcmp(argv[0], "exit") == 0)
            return;
        
        if(strlen(redirections) > 2) {
            execute_redir(argv, redirections);
        } else {
            if(fork() == 0) {
                err = execvp(argv[0], argv);
                printf("%s: command not found!\n", argv[0]);
            }
        }

        if(err == -1) /* child exits */
            exit(1);
        
        wait((char*)NULL); /*parent waits till the command execution */
        free(argv);
        printf("\n%s", prompt);
    }
    printf("\n");
}

int main(void)
{
    const char prompt[] = "$ ";
    shell(prompt);
    return 0;
}
/*
                if (dup2(std_out, STDOUT_FILENO) == -1)
                    error("output to stdout");*/
