/*
reverse a list iteratively.
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
void reverse(struct node** ref_plist);

int main()
{   
    struct node* plista = create_list();
    print(plista);
    reverse(&plista);
    printf("after reversal the list is :\n");
    print(plista);

    printf("\n");
    return 0;
}


void move_node(struct node** dest, struct node** source);
void reverse(struct node** ref_plist)
{
    struct node* plast= *ref_plist;
    *ref_plist = NULL;
    while (plast != NULL) {
        move_node(ref_plist, &plast);
    }
}


void push_node(struct node** ref_plist, struct node* pnode);
struct node* pop_node(struct node** ref_plist);
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

