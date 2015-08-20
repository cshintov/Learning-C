/* given a binary search tree convert it to a circular doubly linked list */

#include <stdio.h>
#include <assert.h>
#include "utils.h"
void print_backwards(struct node* plist, struct node* pend);
void print_c_lnk_lst(struct node* plist, struct node* phead)
{
    if (plist == NULL) {
        printf("Empty List!\n");
        return;
    }
    printf("%d %s",plist->data,(plist->right == phead)? "\n" : "<=> ");
    if (plist->right == phead) {      //end of the circular linked list
        print_backwards(plist, plist);
        return; 
    }
    print_c_lnk_lst(plist->right, phead);    
}

void print_backwards(struct node* plist, struct node* pend)
{
    if (plist == NULL) {
        printf("Empty List!\n");
        return;
    }
    printf("%d %s",plist->data,(plist->left == pend)? "\n" : "<=> ");
    if (plist->left == pend)
        return;
    print_backwards(plist->left, pend);
}

void print_cir_link_list(struct node* plist)
{
    print_c_lnk_lst(plist, plist);        
}

struct node* build_cll123()
{
    struct node* phead = new_node(1);
    struct node* temp = new_node(2);
    phead->right = temp;
    temp->left = phead;
    struct node* temp2 = new_node(3);
    temp->right = temp2;
    temp2->left = temp;
    
    temp2->right = phead;
    phead->left = temp2;
    
    return phead;    
}

void helper(struct node* root, struct node** lt_leaf, struct node** rt_leaf);

struct node* tree_to_list(struct node* root)
{
    if (root == NULL)
        return root;
    if (is_leaf(root)) {
        root->left = root;
        root->right = root;
        return root;
    }
    struct node* head = NULL;
    struct node* end = NULL;
    struct node* temp = NULL;
    if (root->left != NULL) {
        helper(root->left, &head, &end); 
        root->left = end;
        root->left->right = root;
        temp = head; 
    } else {
        temp = root;
    }
    if (root->right != NULL) {
        helper(root->right, &head, &end); 
        root->right = head;
        root->right->left = root;
    } else {
        end = root;
    }
    
    temp->left = end;  
    end->right = temp;
    return temp;
}

void helper(struct node* root, struct node** lt_leaf, struct node** rt_leaf)
{
    if (root == NULL || is_leaf(root)) {
        *lt_leaf = root;
        *rt_leaf = root;
        return;
    }
    struct node* head = NULL;
    struct node* end = NULL;
    if (root->left != NULL) {
        helper(root->left, &head, &(root->left)); 
        root->left->right = root;
    }
    if (head == NULL)
        head = root;
    *lt_leaf = head;
    if (root->right != NULL) {
        helper(root->right, &(root->right), &end); 
        root->right->left = root;
    }
    if (end == NULL)
        end = root;
    *rt_leaf = end;
}


int main()
{
    //struct node* plist;
    //plist = build_cll123();
    //print_cir_link_list(plist);
    struct node* ptree = build_bstree();
    print_tree(ptree, in_order);
    struct node* plist = tree_to_list(ptree);
    print_cir_link_list(plist);

    return 0;
}
