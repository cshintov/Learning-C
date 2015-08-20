/* counts the number of nodes in the tree */
#include <stdio.h>
#include "utils.h"

/* prints the tree in order */
void inorder(struct node* ptree)
{
    if (ptree == NULL)
        return;
    in_order(ptree->left);
    printf("%d ", ptree->data);
    in_order(ptree->right);
}


int main()
{
    printf("\n");
    struct node* ptree = build_bstree();
    inorder(ptree);
    printf("\n\n");
    return 0;
}

