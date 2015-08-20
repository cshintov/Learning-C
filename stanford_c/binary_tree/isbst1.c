/* checks whether a binary tree is binary search tree */
#include <stdio.h>
#include <assert.h>
#include "utils.h"
#include <limits.h>
/*
Returns true if the given tree is a binary search tree
(efficient version).
*/
int is_bst(struct node* ptree)
{
    return(is_bst_recur(ptree, INT_MIN, INT_MAX));
}

int left_check(struct node* ptree, int max)
{
    assert(ptree != NULL);
    int left, right;
    left = right = FALSE;
    if (ptree->right == NULL ||
            (ptree->right->data >= ptree->data && ptree->right->data <= max))
        right = TRUE;
    if (ptree->left == NULL || ptree->left->data <= ptree->data)
        left = TRUE;
    if (left && right)
        return TRUE;
    return FALSE;
}


int right_check(struct node* ptree, int min)
{
    assert(ptree != NULL);
    int left, right;
    left = right = FALSE;
    if (ptree->left == NULL ||
            (ptree->left->data <= ptree->data  && ptree->left->data >= min))
        left = TRUE;
    if (ptree->right == NULL || ptree->right->data >= ptree->data)
        right = TRUE;
    if (left && right)
        return TRUE;
    return FALSE;
}

/*
Returns true if the given tree is a BST and its
values are >= min and <= max.
*/
int is_bst_recur(struct node* ptree, int min, int max)
{
    if (ptree == NULL || is_leaf(ptree))
        return TRUE;
    if (left_check(ptree, max) &&
            right_check(ptree, min))
        if (is_bst_recur(ptree->left, min, ptree->data) &&
                is_bst_recur(ptree->right, ptree->data, max))
            return TRUE;
        return FALSE;
    return FALSE;
}


int main()
{
    struct node* ptree = build_btree();
    print_tree(ptree, in_order);
    if(is_bst(ptree))
        printf("The tree is binary search Tree\n");
    else
        printf("The tree is not binary search tree\n");
    return 0;
}
