/* binary tree utility functions */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int lookup(struct node* ptree, int data)
{
    if (ptree == NULL)
        return FALSE;
    if (data == ptree->data)
        return TRUE;
    else if (data < ptree->data)
        return lookup(ptree->left, data);
    else
        return lookup(ptree->right, data);
}


/* prints the tree in order, return FALSE if empty else TRUE */
int in_order(struct node* ptree)
{
    if (ptree == NULL)
        return FALSE;
    in_order(ptree->left);
    printf("%d ", ptree->data);
    in_order(ptree->right);
    return TRUE;
}

struct node* insert(struct node* ptree, int data)
{
    if(ptree == NULL)
        return(new_node(data));
    if(data <= ptree->data)
        ptree->left = insert(ptree->left, data);
    else
        ptree->right = insert(ptree->right, data);
    return  ptree;
}

struct node* new_node(int data)
{
    struct node* pnew = malloc(sizeof(struct node));
    pnew->data = data;
    pnew->left = NULL;
    pnew->right = NULL;
    return pnew;
}


struct node* build_bstree()
{
    char choice;
    int num;
    struct node* ptree = NULL;
    printf("Create a tree? : y: yes, n: no-->");
    scanf("%c", &choice);
    getchar();
    while (choice != 'n') {
        printf("enter the number:\n");
        scanf("%d", &num);
        getchar();
        ptree = insert(ptree, num);
        printf("continue ? : y:yes, n:no->> ");
        scanf("%c", &choice);
        getchar();
    }
    printf("\n");
    return ptree;
}


struct node* build_123()
{
    struct node* ptree = NULL;
    ptree = insert(ptree, 1);
    ptree = insert(ptree, 2);
    ptree = insert(ptree, 3);
    return ptree;
}


int size(struct node* ptree)
{
    if (ptree == NULL)
        return 0;
    return 1 + size(ptree->left) + size(ptree->right);
}


/* prints the tree in post order, return FALSE if empty else TRUE */
int post_order(struct node* ptree)
{
    if (ptree == NULL)
        return FALSE;
    post_order(ptree->left);
    post_order(ptree->right);
    printf("%d ", ptree->data);
	return TRUE;
}


int is_leaf(struct node* node)
{
	if (node->left == NULL && node->right == NULL)
		return TRUE;
	return FALSE;
}


void swap(struct node** pleft, struct node** pright)
{
	struct node* temp;
	temp = *pleft;
	*pleft = *pright;
	*pright = temp;	
}


void insert_left(struct node* ptree, int data)
{
    struct node* new;
    new = new_node(data);
    new->left = ptree->left;
    ptree->left = new;
}


void insert_right(struct node* ptree, int data)
{
    struct node* new;
    new = new_node(data);
    new->right = ptree->right;
    ptree->right = new;
}


void print_tree(struct node* ptree, int order())
{
    printf("\nThe Tree: ");
    if(!order(ptree))
        printf("Empty Tree!");;
    printf("\n");
}


struct node* insert_node(struct node* ptree, int nod_val, int data, char side)
{
    if (ptree == NULL)
        return new_node(data);
    if (nod_val == ptree->data)
        if (side == 'l')
            insert_left(ptree, data);
        else
            insert_right(ptree, data);
    if (ptree->left != NULL)
        ptree->left = insert_node(ptree->left, nod_val, data, side);
    if (ptree->right != NULL)
        ptree->right = insert_node(ptree->right, nod_val, data, side);
    return ptree;
}


struct node* build_btree()
{
    char choice, side;
    int num, nod_val;
    struct node* ptree = NULL;
    printf("Create a tree? : y: yes, n: no-->");
    scanf("%c", &choice);
    getchar();
    if (choice != 'n') {
        printf("Usage: 1.Enter the node under which to insert the new number\n");
        printf("2.The number to insert\n");
        printf("3.Side: l for left and r for right\n");
    }
    while (choice != 'n') {
        printf("enter the node, number, side(l/r) in that order:\n");
        scanf("%d %d %c", &nod_val, &num, &side);
        getchar();
        ptree = insert_node(ptree, nod_val, num, side);
        printf("continue ? : y:yes, n:no->> ");
        scanf("%c", &choice);
        getchar();
    }
    printf("\n");
    return ptree;
}


