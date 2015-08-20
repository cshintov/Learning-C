/* prints the tree in post order */
#include <stdio.h>
#include "utils.h"

int post_order(struct node* ptree)
{
    if (ptree == NULL)
        return FALSE;
    post_order(ptree->left);
    post_order(ptree->right);
    printf("%d ", ptree->data);
	return TRUE;
}


int main()
{
    printf("\n");
    struct node* ptree = build_bstree();
    if(!post_order(ptree))
		printf("Empty tree!\n");
    printf("\n\n");
    return 0;
}

