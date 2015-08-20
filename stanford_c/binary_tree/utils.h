/* declrations for utility functions */
#define TRUE 1
#define FALSE 0
#define CONTINUE 2
#define LEFT 3
#define RIGHT 4
struct node {
    int data;
    struct node*  left;
    struct node* right;
};

int lookup(struct node* pnode, int data);
int in_order(struct node* ptree);
int post_order(struct node* ptree);
void print_tree(struct node* ptree, int order());
int size(struct node* ptree);
int is_leaf(struct node* node);
void swap(struct node** pleft, struct node** pright);
void insert_left(struct node* ptree, int data);

/* binary tree creation utilities */
struct node* insert_node(struct node* ptree, int nod_val, int data, char side);
struct node* build_btree();

/* binary search tree creation utilites */
struct node* insert(struct node* pnode, int data);
void insert_left(struct node* ptree, int data);
void insert_right(struct node* ptree, int data);
struct node* new_node(int data);
struct node* build_bstree();
struct node* build_123();
