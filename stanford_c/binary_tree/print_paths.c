/* prints all the branches */

#include <stdio.h>
#include "utils.h"


void print_ancestors(int paths[], int len)
{
	int i;
	for(i = 0; i < len; i++)
		printf("%d ", paths[i]);
}


void pp_helper(struct node* ptree, int paths[], int len)
{
    if (ptree == NULL)
        return;
	if (is_leaf(ptree)) {
		print_ancestors(paths, len);
		printf("%d\n", ptree->data);
	} else {
		paths[len++] = ptree->data;
		pp_helper(ptree->left, paths, len);
		pp_helper(ptree->right, paths, len);
	}
}


void print_paths(struct node* ptree)
{
	static int paths[50]; // initial val zero automatically
	pp_helper(ptree, paths, 0);
}


int kk()
{
    printf("\n");
    struct node* ptree = build_bstree();
    if(!in_order(ptree))
		printf("Empty tree!\n");
    printf("\n");
    print_paths(ptree);
    printf("\n\n");
    return 0;
}

