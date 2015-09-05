#define MAXSIZE 50
#define REDSIZE 20
#define TRUE 1
#define FALSE 0
#define IN_RED '<'
#define OUT_RED '>'
#define PIPE '|'
#define NONE 0
char* get_str(char *s, int size);
char** get_argv(char *s);
char* get_redirections(char* s);
char** get_comm(char** argv);
