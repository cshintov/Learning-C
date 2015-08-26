/* binary tree utility functions */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>

char* lookup(struct node* ptree, int data)
{
    if (ptree == NULL)
        return NULL;
    if (data == ptree->data)
        return ptree->opname;
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
    printf("0x%x %s\n", ptree->data, ptree->opname);
    in_order(ptree->right);
    return TRUE;
}

struct node* insert(struct node* ptree, unsigned int data, char* string)
{
    struct node* pnode;
    if(ptree == NULL){
        pnode = new_node(data, string);
        return pnode;
    }
    if(data <= ptree->data){
        ptree->left = insert(ptree->left, data, string);
    }
    else {
        ptree->right = insert(ptree->right, data, string);
    }
    return  ptree;
}

struct node* new_node(unsigned int data, char *string)
{
    struct node* pnew = malloc(sizeof(struct node));
    if(pnew == NULL)
        printf("No more heap!\n");
    pnew->data = data;
    strncpy(pnew->opname, string, sizeof(pnew->opname)); 
    pnew->left = NULL;
    pnew->right = NULL;
    return pnew;
}

int size(struct node* ptree)
{
    if (ptree == NULL)
        return 0;
    return 1 + size(ptree->left) + size(ptree->right);
}


int is_leaf(struct node* node)
{
	if (node->left == NULL && node->right == NULL)
		return TRUE;
	return FALSE;
}


void insert_left(struct node* ptree, unsigned int data, char *opname)
{
    struct node* new;
    new = new_node(data, opname);
    new->left = ptree->left;
    ptree->left = new;
}


void insert_right(struct node* ptree, unsigned int data, char* opname)
{
    struct node* new;
    new = new_node(data, opname);
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

