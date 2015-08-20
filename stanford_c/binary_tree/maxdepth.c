/* computes the maxdepth of the tree, where maxdepth is the
heighest number of nodes along all branches */
#include <stdio.h>
#include "utils.h"

int main()
{
    printf("\n");
    struct node* ptree = build_bstree();
    in_order(ptree);
    printf("depth of the tree is:%d\n",max_depth(ptree));
    printf("\n\n");
    return 0;
}


int max_depth(struct node* ptree)
{
    if (ptree == NULL)
        return 0;
    int left = max_depth(ptree->left);    
    int right = max_depth(ptree->right);
    if (left > right)
        return left + 1;
    else
        return right + 1;    
}
