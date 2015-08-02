// compute word frequency and print them in decreasing order of frequency
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
struct cnode {
    int count;
    int ns;
    char *words[MAXWORD/2];
    struct cnode *left;
    struct cnode *right;
};
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};


int getword(char *word, int lim);
struct tnode* insert(struct tnode* node, char *word);
void treeprint(struct tnode* root);
struct cnode* cinsert(struct cnode*, struct tnode*);
void ctreeprint(struct cnode* root);
struct cnode* create(struct cnode*, struct tnode*);
int main()
{   
    struct tnode *root ;
    struct cnode *croot;
    char word[MAXWORD];

    root = NULL;
    while(getword(word, MAXWORD) != EOF)
        if(isalpha(word[0]))
            root = insert(root, word);
    
    croot = NULL;
    croot = create(croot, root);
    ctreeprint(croot);
    return 0;
}


struct tnode* talloc(void);
char *mystrdup(char *word);

struct tnode *insert(struct tnode *node, char *word)
{   
    int cond;

    if(node == NULL) {
        node = talloc();
        node->word = mystrdup(word);
        node->count = 1;
        node->left = node->right = NULL;
    } else if((cond = strcmp(word, node->word)) == 0)
        node->count++;
    else if(cond < 0)
        node->left = insert(node->left, word);
    else 
        node->right = insert(node->right, word);
    return node;

}

void treeprint(struct tnode *node)
{
    if(node != NULL) {
        treeprint(node->right);
        printf("%4d %s\n", node->count, node->word);
        treeprint(node->left);
    }
}

#include <stdlib.h>
struct tnode *talloc(void)
{
    return (struct tnode*) malloc(sizeof(struct tnode));
}
struct cnode *tcalloc(void)
{
    return (struct cnode*) malloc(sizeof(struct cnode));
}

char *mystrdup(char *word)
{
    char *p;
    p = (char *) malloc(strlen(word) + 1);
    if(p != NULL)
        p = strcpy(p, word);
    return p;
}


int getword(char *word, int lim)
{
    int getch(void), c;
    void ungetch(int);
    char *w = word;

    while(isspace(c = getch()))
        ;
    if(c != EOF)
        *w++ = c;
    if(!isalpha(c)){
        *w = '\0';
        return c;
    }
    for(; --lim > 0; w++)
        if(!isalnum(*w = getch())){
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
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




/* code for second tree
traverse the tree , for each count, if it is already present in the new tree add the corresponding word at the nodes string list

traverse the new tree , for each node print the list of strings with preceding count
*/
struct cnode *create(struct cnode *croot, struct tnode *root)
{
    croot = cinsert(croot, root);
    if(root->left != NULL)
        croot = create(croot, root->left);
    if(root->right!= NULL)
        croot = create(croot, root->right);
    return croot;
}

struct cnode *cinsert(struct cnode *croot, struct tnode *node)
{
    if(croot == NULL) {
        croot = tcalloc();
        croot->count = node->count;
        croot->ns = 0;
        croot->words[croot->ns++] = node->word;
        croot->words[croot->ns] = NULL;
        croot->left = croot->right = NULL;
    } else if(croot->count == node->count)
        croot->words[croot->ns++] = node->word;
    else if(croot->count > node->count)
        croot->left = cinsert(croot->left, node);
    else if(croot->count < node->count)
        croot->right= cinsert(croot->right, node);
    return croot;
}

void ctreeprint(struct cnode* croot)
{
    if(croot != NULL) {
        ctreeprint(croot->right);
        char **w = croot->words;
        while(*w != NULL){
            printf("%d %s\n", croot->count, *w);
            w++;
        }
        ctreeprint(croot->left);
    }
}
