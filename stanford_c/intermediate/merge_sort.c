/* Implement mergesort using frontback_split and sorted_merge */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

struct node {
    int data;
    struct node* next;
};

struct node* create_list();
void print(struct node* plist);
void merge_sort(struct node** ref_plist);

int main()
{   
    struct node* plist = create_list();
    print(plist);
    merge_sort(&plist);
    printf("after sorting:\n");
    print(plist);

    printf("\n");
    return 0;
}


int length(struct node* plist);
struct node* sorted_merge(struct node* plista, struct node* plistb);
void front_back_split(struct node* source,
                    struct node** ref_front, struct node** ref_back);

void merge_sort(struct node** ref_plist)
{
    if (length(*ref_plist) <= 1)
        return;
    struct node* front;
    struct node* back;
    front_back_split(*ref_plist, &front, &back);
    merge_sort(&front);
    merge_sort(&back);
    *ref_plist = sorted_merge(front, back);
}


void move_node(struct node** dest, struct node** source);
int rest_merge(struct node** ref_plast, struct node* plista,
                struct node* plistb);
/*
Takes two lists sorted in increasing order, and
splices their nodes together to make one big
sorted list which is returned.
*/
struct node* sorted_merge(struct node* plista, struct node* plistb)
{
    struct node* phead = NULL;
    struct node** ref_plast = &phead;
    while(plista != NULL || plistb != NULL) {
        if(rest_merge(ref_plast, plista, plistb))
            return phead;
        if(plista->data < plistb->data) {
            move_node(ref_plast, &plista);
            ref_plast = &((*ref_plast)->next);
        } else {
            move_node(ref_plast, &plistb);
            ref_plast = &((*ref_plast)->next);
        }
    }
    return phead;
}


/* does the last bit of sorted merge ie, if any of the list is empty */
int rest_merge(struct node** ref_plast, struct node* plista,
                struct node* plistb)
{
    if (plista == NULL) {
        *ref_plast = plistb;
        return TRUE;    
    } else if (plistb == NULL) {
        *ref_plast = plista;
        return TRUE;
    }
    return FALSE;
}

/*
Merge the nodes of the two lists into a single list taking a node
alternately from each list, and return the new list.
*/
struct node* shuffle_merge(struct node* plista, struct node* plistb)
{
    struct node* phead = NULL;
    struct node** ref_plast = &phead;
    while(plista != NULL || plistb != NULL) {
        if(rest_merge(ref_plast, plista, plistb))
            return phead;
        if(plista != NULL) {
            move_node(ref_plast, &plista);
            ref_plast = &((*ref_plast)->next);
        }
        if(plistb != NULL) {
            move_node(ref_plast, &plistb);
            ref_plast = &((*ref_plast)->next);
        } 
    }
    return phead;
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

