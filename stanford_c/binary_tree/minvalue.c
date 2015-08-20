/* computes the minimum value in the binary search tree*/ 
#include <assert.h>
#include <stdio.h>
#include "utils.h"

int main()
{
    printf("\n");
    struct node* ptree = build_bstree();
    in_order(ptree);
    printf("min val of the tree is:%d\n",min_value(ptree));
    printf("max val of the tree is:%d\n",max_value(ptree));
    printf("\n\n");
    return 0;
}


int min_value(struct node* ptree)
{
    assert(ptree != NULL);
	if(ptree->left == NULL)
		return ptree->data;
	else
		return min_value(ptree->left);
}


int max_value(struct node* ptree)
{
    assert(ptree != NULL);
	if(ptree->right == NULL)
		return ptree->data;
	else
		return max_value(ptree->right);
}
