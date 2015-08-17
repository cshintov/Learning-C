#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int data;
    struct node* next;
};

void print(struct node* plist);
int length(struct node* plist);
struct node* build_n_nodes(int num);
struct node* create_list();
void insert_sort(struct node** ref_plist);

int main()
{   
    struct node* plist = create_list();
    printf("The length of the list is :%d\n", length(plist));
    print(plist);
    insert_sort(&plist);
    printf("After sorting:\n");
    print(plist);
    printf("\n");
    return 0;
}


void sorted_insert(struct node** ref_plist, struct node* pnew);
struct node* pop_min_node(struct node** ref_plist);
void insert_sort(struct node** ref_plist)
{
    struct node** current = ref_plist;
    struct node* min_node;
    while((*current)->next != NULL) {
        min_node = pop_min_node(current);
        sorted_insert(current, min_node);
        current = &((*current)->next);
    }
}


struct node* pop_min_node(struct node** ref_plist)
{
    assert(*ref_plist != NULL);
    struct node** ref_head = ref_plist;
    struct node* pmin_node = *ref_plist;
    struct node* prev_node = pmin_node;
    int min = (*ref_plist)->data;
    while(*ref_plist != NULL && (*ref_plist)->next != NULL) {
        if ((*ref_plist)->next->data < min) {
            min = (*ref_plist)->next->data;
            pmin_node = (*ref_plist)->next;
            prev_node = *ref_plist;
        }
        ref_plist = &((*ref_plist)->next);
    }
    if (prev_node == pmin_node)         // first node is the min node
        *ref_head = (*ref_head)->next;
    else
        prev_node->next = pmin_node->next;
    return pmin_node;
}


void append(struct node** ref_plist, int data);
struct node* create_list()
{
    char choice;
    int num;
    struct node* plist = NULL;
    printf("Create a List? : y: yes, n: no-->");
    scanf("%c", &choice);
    while (choice != 'n') {
         scanf("%d", &num);
         append(&plist, num);
         printf("continue ? : y:yes, n:no->> ");
         scanf(" %c", &choice);
    }
    return plist;
}

void sorted_insert(struct node** ref_plist, struct node* pnew)
{
    struct node** ref_previous = NULL;
    if (*ref_plist == NULL)
        *ref_plist = pnew;
    else {
        while (*ref_plist != NULL && (*ref_plist)->data <= pnew->data) {
            ref_previous = ref_plist;
            ref_plist = &((*ref_plist)->next);
        }
        if (ref_previous != NULL) {
            pnew->next = (*ref_previous)->next;
            (*ref_previous)->next = pnew;
        } else {
            pnew->next = *ref_plist;
            *ref_plist = pnew;
        }
    }
}


void add_left(struct node** ref_pnode, int data);
void insert(struct node** ref_plist, int data, int index)
{
    while(index-- > 0) {
        ref_plist = &((*ref_plist)->next);
    }
    add_left(ref_plist, data);
}


int pop(struct node** ref_plist)
{
    assert(*ref_plist != NULL);
    struct node* pnew_head = (*ref_plist)->next;
    int data = (*ref_plist)->data;
    free(*ref_plist);
    *ref_plist = pnew_head;
    return data;
}


void delete_list(struct node ** ref_plist)
{
    struct node* pnext;
    struct node* pcurrent = *ref_plist;
    while(pcurrent != NULL) {
        pnext = pcurrent->next;
        free(pcurrent);
        pcurrent = pnext;
    }
    *ref_plist = NULL;
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
