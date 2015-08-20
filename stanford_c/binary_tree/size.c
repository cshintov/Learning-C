/* counts the number of nodes in the tree */
#include <stdio.h>
#include "utils.h"

int main()
{
    printf("\n");
    struct node* ptree = build_bstree();
    in_order(ptree);
    printf("size of the tree is:%d\n",size(ptree));
    printf("\n\n");
    return 0;
}


int size(struct node* ptree)
{
    if (ptree == NULL)
        return 0;
    return 1 + size(ptree->left) + size(ptree->right);
}
