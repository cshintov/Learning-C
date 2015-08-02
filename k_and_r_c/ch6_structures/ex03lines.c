// prints words wither their line numbers
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 1000
#define MAXWORD 100
struct tnode {
    int lnum;
    char *word;
    int nl;
    int lines[MAXLINES];
    struct tnode *left;
    struct tnode *right;
};


int getword(char *word, int lim, int lnum);
struct tnode* insert(struct tnode* node, char *word, int lnum);
void treeprint(struct tnode* root);

int main()
{   
    struct tnode *root ;
    char word[MAXWORD];
    int lnum = 0;

    root = NULL;
    while((lnum = getword(word, MAXWORD, lnum)) > 0)
        if(isalnum(word[0]))
            root = insert(root, word, lnum);
    
    treeprint(root);
    return 0;
}


struct tnode* talloc(void);
char *mystrdup(char *word);


struct tnode *insert(struct tnode *root, char *word, int lnum)
{
    int cond;
    if(root == NULL) {
        root = talloc();
        root->word = mystrdup(word);
        root->nl = 0;
        root->lines[root->nl++] = lnum;
        root->lines[root->nl] = 0;
        root->left = root->right = NULL;
    } else if((cond = strcmp(word, root->word)) == 0)
        root->lines[root->nl++] = lnum;
    else if(cond < 0)
        root->left = insert(root->left, word, lnum);
    else 
        root->right= insert(root->right, word, lnum);
    return root;
}
void treeprint(struct tnode* root)
{
    if(root != NULL) {
        treeprint(root->left);
        int *lines = root->lines;
        printf("%s :", root->word);
        while(*lines != 0){
            printf(" %d", *lines);
           lines++;
        }
        printf("\n");
        treeprint(root->right);
    }
}

#include <stdlib.h>
struct tnode *talloc(void)
{
    return (struct tnode*) malloc(sizeof(struct tnode));
}

char *mystrdup(char *word)
{
    char *p;
    p = (char *) malloc(strlen(word) + 1);
    if(p != NULL)
        p = strcpy(p, word);
    return p;
}


int getword(char *word, int lim, int line)
{
    int getch(void), c;
    void ungetch(int);
    char *w = word;

    while(isspace(c = getch()) || ispunct(c)){
        if(c == '\n')
            line += 1;
    }
    if(c != EOF)
        *w++ = c;
    else
        return EOF;
    for(; --lim > 0; w++)
        if(isspace(*w = getch()) || ispunct(*w)){
            if(*w == '\n')
                line += 1;
            break;
        }
    *w = '\0';
    return line;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();   
}

void ungetch(int c) {
    if(bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch : Too many values!\n");
}

