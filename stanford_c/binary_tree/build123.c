/* builds the tree  1,2,3 */
#include <stdio.h>
#include "utils.h"

int main()
{
    printf("\n");
    struct node* build_123();
    struct node* ptree = build_123();
    in_order(ptree);
    printf("\n\n");
    return 0;
}

struct node* build_123()
{
    struct node* ptree = NULL;
    ptree = insert(ptree, 1);
    ptree = insert(ptree, 2);
    ptree = insert(ptree, 3);
    return ptree;
}
