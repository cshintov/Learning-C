/* count the number of occurrences of a number */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

void print(struct node* plist);
int length(struct node* plist);
void prepend(struct node** ref_plist, int data);
void append(struct node** ref_plist, int data);
struct node* build_n_nodes(int num);
int count(struct node* plist, int data);
int main()
{   
    struct node *plist = NULL;
    printf("The count fo value %d in the list is %d\n", 1, count(plist, 1));
    plist = build_n_nodes(3);
    prepend(&plist, 4);
    append(&plist,5);
    prepend(&plist, 2);
    append(&plist, 2);
    append(&plist, 1);
    printf("The length of the list is :%d\n", length(plist));
    print(plist);
    
    printf("The count of value %d in the list is %d\n", 1, count(plist, 1));
    printf("\n");
    return 0;
}


int count(struct node* plist, int data)
{
    struct node *pcurrent = plist;
    int count = 0;
    while(pcurrent != NULL) {
        if(pcurrent->data == data)
            count++;
        pcurrent = pcurrent->next;
    }
    return count;
}


struct node* build_three_nodes()
{   
    struct node *list;

    list = malloc(sizeof(struct node));
    
    list->data = 1;
    list->next = malloc(sizeof(struct node));

    list->next->data = 2;
    list->next->next = malloc(sizeof(struct node));

    list->next->next->data = 3;
    list->next->next->next= NULL;
    return list;
}

void print(struct node* list)
{
    struct node *current = list;
    
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


struct node* create_node(int data);

struct node* copy_list(struct node* plist)
{
    struct node *pcurrent = NULL; 
    struct node *phead = NULL; 
    struct node *ptail = NULL;
    if (plist == NULL)
        return plist;
    pcurrent = plist;                   // head of the input list
    add_right(&phead, pcurrent->data); // head of the copy list
    ptail = phead;
    while (pcurrent->next != NULL) {
        add_right(&ptail, pcurrent->next->data);
        ptail = ptail->next;
        pcurrent = pcurrent->next;
    }
    return phead;   // returns the head of the copy list
}

struct node* copy_local_ref(struct node* plist)
{
    struct node *pcurrent = plist;
    struct node *pnew_head = NULL;
    struct node **ref_last_ptr = &pnew_head;
    while(pcurrent != NULL) {
        add_right(ref_last_ptr, pcurrent->data);
        ref_last_ptr = &((*ref_last_ptr)->next);
        pcurrent = pcurrent->next;
    }
    return pnew_head;
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


/*
alternative implementation of prepend function
we can call prepend like this:
void calling_func(){
    struct node* list = NULL;
    list = prepend(list, 3);
    // do something with list
}
struct node* prepend(struct node* list, int data)
{
    struct node *new = malloc(sizeof(struct node));
    new->data = data;
    new->next = list;
    return new;
}
*/



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
