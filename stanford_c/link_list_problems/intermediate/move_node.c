/*
Take the node from the front of the source, and move it to
the front of the dest.
It is an error to call this with the source list empty.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int data;
    struct node* next;
};

struct node* create_list();
void print(struct node* plist);
int length(struct node* plist);
void move_node(struct node** dest, struct node** source);

int main()
{   
    struct node *plista = create_list();
    struct node *plistb = create_list();
    print(plista);
    print(plistb);
    move_node(&plista, &plistb);
    printf("after move_head:\n");
    print(plista);
    print(plistb);

    printf("\n");
    return 0;
}


struct node* pop_node(struct node** ref_plist);
void push_node(struct node** ref_plist, struct node* pnode);
/*
Take the node from the front of the source, and move it to
the front of the dest.
It is an error to call this with the source list empty.
*/
void move_node(struct node** dest, struct node** source)
{
    struct node* source_head = pop_node(source);
    push_node(dest, source_head);
}

void push_node(struct node** ref_plist, struct node* pnode)
{
    pnode->next = (*ref_plist);
    *ref_plist = pnode;        
}
    

struct node* pop_node(struct node** ref_plist)
{
    assert(*ref_plist != NULL);
    struct node* top = *ref_plist;
    *ref_plist = (*ref_plist)->next;
    top->next = NULL;
    return top;        
}


void delete_node(struct node** node);
void remove_duplicates(struct node* head)
{ 
    if (head == NULL)
        return;
    struct node** ref_current = &head;
    while((*ref_current)->next != NULL) {
        if((*ref_current)->data == (*ref_current)->next->data)
            delete_node(&(*ref_current)->next);
        ref_current = &((*ref_current)->next);
        if(*ref_current == NULL)
            break;
    }
}

void delete_node(struct node** ref_current)
{
    assert(*ref_current != NULL);
    struct node* temp = *ref_current;
    *ref_current = (*ref_current)->next;
    free(temp);
}

void print(struct node* list)
{
    struct node *current = list;
    if (current == NULL)
        printf("Empty list!\n");
    while (current != NULL){
        printf("|%d|%s", current->data, (current->next != NULL) ? "->" : "\n");
        current = current->next;
    }
}


int length(struct node* list)
{
    struct node *current = list;
    int count = 0;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

void add_left(struct node** ref_pnode, int data);
void add_right(struct node** ref_pnode, int data);

void prepend(struct node** ref_plist, int data)
{
    add_left(ref_plist, data);
}


void append(struct node** ref_plist, int data)
{
    struct node *pcurrent = *ref_plist;

    if (pcurrent == NULL) {          // empty list, add left to it
        add_left(ref_plist, data);
    } else {                        // find the last node, add right to it
        while(pcurrent->next != NULL)
            pcurrent = pcurrent->next;
        add_right(&pcurrent, data);
    }
}

struct node* create_node(int data)
{
    struct node *new_head = malloc(sizeof(struct node));
    new_head->data = data;
    new_head->next = NULL;
    return new_head;
}


void add_left(struct node** ref_pnode, int data)
{
    struct node *new_head = create_node(data);
    new_head->next = *ref_pnode;
    *ref_pnode = new_head;
}


void add_right(struct node** ref_pnode, int data)
{
    if(*ref_pnode != NULL) {
        struct node **ref_pnext = &((*ref_pnode)->next);
        add_left(ref_pnext, data);
    } else
        add_left(ref_pnode, data);
}


struct node* build_n_nodes(int num)
{
    struct node **ref_plast;
    struct node *phead = NULL;
    int i;
    ref_plast = &phead;
    for(i = 0; i < num; i++) {
        prepend(ref_plast, i);
        ref_plast = &((*ref_plast)->next);
    }
    return phead;
}


struct node* create_list()
{
    char choice;
    int num;
    struct node* plist = NULL;
    printf("Create a List? : y: yes, n: no-->");
    scanf("%c", &choice);
    getchar();
    while (choice != 'n') {
         scanf("%d", &num);
         getchar();         // for consuming the newline character
         append(&plist, num);
         printf("continue ? : y:yes, n:no->> ");
         scanf("%c", &choice);  
         getchar();         // for consuming the newline character
    }
    return plist;
}

