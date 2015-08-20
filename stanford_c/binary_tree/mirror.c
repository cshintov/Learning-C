/* modifies the tree to its mirror image */
#include <stdio.h>
#include "utils.h"

void mirror(struct node* ptree)
{
    if (ptree == NULL || is_leaf(ptree))
		return;
	mirror(ptree->left);
	mirror(ptree->right);
	swap(&ptree->left, &ptree->right);
}


int main()
{
    printf("\n");
    struct node* ptree = build_bstree();
    if(!in_order(ptree))
		printf("Empty tree!\n");
    printf("\n");
    mirror(ptree);
	printf("printing the mirror!\n");
    if(!in_order(ptree))
		printf("Empty tree!\n");
    printf("\n\n");
    return 0;
}
