/*
Split the nodes of the given list into front and back halves,
and return the two lists using the reference parameters.
If the length is odd, the extra node should go in the front list.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int data;
    struct node* next;
};

void print(struct node* plist);
struct node* build_n_nodes(int num);
void front_back_split(struct node* source,
                    struct node** frontRef, struct node** backRef);

int main()
{   
    struct node *plista = build_n_nodes(5);
    struct node *front, *back;
    printf("list a is:\n");
    print(plista);

    front_back_split(plista, &front, &back);
    printf("after split, list front is:\n");
    print(front);
    printf("after split , list back is:\n");
    print(back);

    printf("\n");
    return 0;
}


void front_back_split(struct node* source,
                    struct node** ref_front, struct node** ref_back)
{
    struct node *fast, *slow;
    int node_pos = 1;
    fast = slow = source;
    int len = length(source);
    if (len < 2) {
        if (len == 0)
            *ref_front = NULL;
        else
            *ref_front = source;
        *ref_back = NULL;
    } else {
        while(fast->next != NULL) {
            if (node_pos % 2 == 0)
                slow = slow->next;
            fast = fast->next;
            node_pos++;
        }
        /* After this loop fast reaches the end of the list and
         * the slow reaches the half of the list.
         * Now split at slow node. 
         */
        *ref_front = source;
        *ref_back = slow->next;
        slow->next = NULL;
    }
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
