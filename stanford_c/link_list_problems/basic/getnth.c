/* get the nth element of the list */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int data;
    struct node* next;
};

void print(struct node* plist);
int length(struct node* plist);
void prepend(struct node** ref_plist, int data);
void append(struct node** ref_plist, int data);
struct node* build_n_nodes(int num);
int get_nth(struct node* plist, int index);

int main()
{   
    struct node *plist = NULL;
    plist = build_n_nodes(3);
    prepend(&plist, 4);
    append(&plist,5);
    prepend(&plist, 2);
    append(&plist, 2);
    append(&plist, 1);
    printf("The length of the list is :%d\n", length(plist));
    print(plist);
    printf("The %d th value is %d\n", 2, get_nth(plist, 1)); 
    printf("\n");
    return 0;
}


int get_nth(struct node* plist, int index)
{
    assert(index >= 0 && index < length(plist)); 
    struct node* pcurrent = plist;
    int i;
    for(i = 0; i < index; i++) {
        pcurrent = pcurrent->next;
    }
    return pcurrent->data;
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
