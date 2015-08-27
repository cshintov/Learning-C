
/* declrations for utility functions */

#define TRUE 1
#define FALSE 0
#define MAXVAL 2000
#define SIZE 1
#define NUM 4
#define HAVE_ARG 90
#define MAXPYC 5000

struct node {
    unsigned int data;
    char opname[20];
    struct node*  left;
    struct node* right;
};

struct field {
    int val[MAXVAL];
    int length;    
};


char* lookup(struct node* pnode, int data);
int in_order(struct node* ptree);
void print_tree(struct node* ptree, int order());
int size(struct node* ptree);
int is_leaf(struct node* node);

struct node* insert(struct node* pnode, unsigned int data, char *s);
void insert_left(struct node* ptree, unsigned int data, char *s);
void insert_right(struct node* ptree, unsigned int data, char *s);
struct node* new_node(unsigned int data, char* string);

/* optab utilities */

struct node* create_optab(char* filename);
char* get_opname(struct node* optab, unsigned int opcode);


/* stack functions */

void push(int data);
int pop(void);

