/* checks whether two binary trees are identical */

#include <stdio.h>
#include "utils.h"

/* checks the empty tree case */
int empty_case(struct node* ptreea, struct node* ptreeb)
{
	if (ptreea == NULL || ptreeb == NULL)
		if(ptreea == ptreeb)
			return TRUE;
		else
			return FALSE;
	return CONTINUE;
}

int same_tree(struct node* ptreea, struct node* ptreeb)
{
	int result = empty_case(ptreea, ptreeb);
	/* checks the empty tree case */
	if (result == TRUE || result == FALSE)
		return result;
	/* result continue: check root data and then subtrees */
	if (ptreea->data != ptreeb->data)
		return FALSE;
	if (same_tree(ptreea->left, ptreeb->left) &&
			same_tree(ptreea->right, ptreeb->right))
			return TRUE;
	return FALSE;
}


int main()
{
	struct node* ptreea = build_bstree();
	struct node* ptreeb = build_bstree();
	print_tree(ptreea, in_order);
	print_tree(ptreeb, post_order);
	if(same_tree(ptreea, ptreeb))
		printf("Trees are identical!\n");
	else
		printf("Trees are NOT identical!\n");
	return 0;
}
