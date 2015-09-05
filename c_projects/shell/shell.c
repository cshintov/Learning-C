#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void execute_redir(char** argv, char* command, char* redirections)
{
    int pid = 1, err = 0, idx = 0;
    int type = NONE;
    char** targv = get_comm(argv);
    /* backup standard input and output */
    int std_in = dup(0);
    int std_out= dup(1);

    while(*argv != NULL) {
        idx = find_redir(argv);
        
        type = which_redir(argv[idx]);
        
        setup_redir(argv, idx);
        
        if (type == IN_RED || type ==  OUT_RED)
            argv += idx + 2;
        else
            argv += idx;
    }
    if((pid = fork()) == 0) {
        err = execvp(targv[0], targv);
        printf("%s: command not found!\n", targv[0]);
    }
    if(err == -1)
        return;
    
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
        argv = get_argv(command);
        redirections = get_redirections(command);

        if(argv[0] == NULL) { /* empty command */
            printf("\n%s", prompt);
            continue;
        }

        if(strcmp(argv[0], "exit") == 0)
            return;
        
        if(*redirections != '\0') {
            execute_redir(argv, command, redirections);
        } else {
            if(fork() == 0) {
                err = execvp(argv[0], argv);
                printf("%s: command not found!\n", argv[0]);
            }
        }
        if(err == -1)
            exit(1);
        wait((char*)NULL); /* wait till the command execution */
        
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
