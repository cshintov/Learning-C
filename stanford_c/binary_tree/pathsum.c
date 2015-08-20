/* checks whether a branch of the tree has given sum */
#include <stdio.h>
#include "utils.h"

int has_path_sum(struct node* ptree, int sum)
{
    if (ptree == NULL)
        return FALSE;
    if (ptree->data == sum && ptree->left == NULL 
                            && ptree->right == NULL)
        return TRUE;
	if (ptree->left != NULL)
		if (has_path_sum(ptree->left, sum - ptree->data))
			return TRUE;
    if (ptree->right != NULL)
	    if(has_path_sum(ptree->right, sum - ptree->data))
            return TRUE;
    return FALSE;
}


int main()
{
    printf("\n");
    struct node* ptree = build_bstree();
    if(!post_order(ptree))
		printf("Empty tree!\n");
    int sum;
    printf("Enter has path sum:\n");
    scanf("%d", &sum);
    if(has_path_sum(ptree, sum))
        printf("There IS such path!\n");
    else
        printf("There is NOT such path!\n");
    printf("\n\n");
    return 0;
}

