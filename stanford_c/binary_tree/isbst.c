/* checks whether a tree is binary search tree */
#include <stdio.h>
#include <assert.h>
#include "utils.h"

int min_val(struct node* ptree)
{
	assert(ptree != NULL);
	int min = ptree->data;
	if (is_leaf(ptree))
		return min;
    if (ptree->left != NULL) {
        int left = min_val(ptree->left);
        if (left <= min)
            min = left;
    }
    if (ptree->right != NULL) {
        int right = min_val(ptree->right);
        if (right < min)
            min = right;
    }
	return min;
}


int max_val(struct node* ptree)
{
	assert(ptree != NULL);
	int max = ptree->data;
	if (is_leaf(ptree))
		return max;
    if (ptree->left != NULL) {
        int left = max_val(ptree->left);
        if (left >= max)
            max = left;
    }
    if (ptree->right != NULL) {
        int right = max_val(ptree->right);
        if (right > max)
            max = right;
    }
	return max;
}

/* if left is bst and maxval(left) <= ptree->data
and (right is bst and minval(right) > ptree->data) 
then ptree is bst
*/

int is_bst(struct node* ptree)
{
    if (ptree == NULL || is_leaf(ptree))
        return TRUE;
    int left_check, right_check;
    left_check = right_check = TRUE;
    if (ptree->left != NULL)
        left_check = is_bst(ptree->left) 
                    && max_val(ptree->left) <= ptree->data;
    if (ptree->right != NULL)
        right_check = is_bst(ptree->right) 
                    && min_val(ptree->right) > ptree->data;

    if (left_check && right_check)
        return TRUE;
    else
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
