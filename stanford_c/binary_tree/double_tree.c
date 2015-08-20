/* adds a node data to its left throughout the tree */
#include <stdio.h>
#include "utils.h"


void double_tree(struct node* ptree)
{
    if (ptree == NULL)
        return;
    if (is_leaf(ptree)) {
        insert_left(ptree, ptree->data);
        return;
    }
    double_tree(ptree->left);
    insert_left(ptree, ptree->data);
    double_tree(ptree->right);
}


int main()
{
    printf("\n");
    struct node* ptree = build_bstree();
    in_order(ptree);
    printf("\n");
    printf("paths before\n");
    print_paths(ptree);
    printf("\n");
    
    double_tree(ptree);

    printf("paths after\n");
    print_paths(ptree);
    printf("\n\n");
    return 0;
}

