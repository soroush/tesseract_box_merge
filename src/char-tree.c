#include "char-tree.h"
#include <stddef.h>
#include <memory.h>

char_tree_t* avl_create_tree() {
    char_tree_t* tree = NULL;
    if((tree = malloc(sizeof(char_tree_t))) == NULL) {
        return NULL;
    }
    tree->root = NULL;
    return tree;
}

char_info_t* avl_create_node() {
    char_info_t* node = NULL;
    if((node = malloc(sizeof(char_info_t))) == NULL) {
        return NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->code = 0;
    node->join_class = 0;
    return node;
}

int avl_node_height(char_info_t* node) {
    int height_left = 0;
    int height_right = 0;
    if(node->left != NULL) {
        height_left = avl_node_height(node->left);
    }
    if(node->right != NULL) {
        height_right = avl_node_height(node->right);
    }
    return height_right > height_left ? ++height_right : ++height_left;
}

int avl_balance_factor(char_info_t* node) {
    int bf = 0;
    if(node->left != NULL) {
        bf += avl_node_height(node->left);
    }
    if(node->right != NULL) {
        bf -= avl_node_height(node->right);
    }
    return bf ;
}

char_info_t* avl_rotate_leftleft(char_info_t* node) {
    char_info_t* a = node;
    char_info_t* b = a->left;
    a->left = b->right;
    b->right = a;
    return(b);
}

char_info_t* avl_rotate_leftright(char_info_t* node) {
    char_info_t* a = node;
    char_info_t* b = a->left;
    char_info_t* c = b->right;
    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;
    return(c);
}

char_info_t* avl_rotate_rightleft(char_info_t* node) {
    char_info_t* a = node;
    char_info_t* b = a->right;
    char_info_t* c = b->left;

    a->right = c->left;
    b->left = c->right;
    c->right = b;
    c->left = a;

    return(c);

}

char_info_t* avl_rotate_rightright(char_info_t* node) {
    char_info_t* a = node;
    char_info_t* b = a->right;

    a->right = b->left;
    b->left = a;

    return(b);
}

char_info_t* avl_balance_node(char_info_t* node) {
    char_info_t* newroot = NULL;

    /* Balance our children, if they exist. */
    if(node->left) {
        node->left  = avl_balance_node(node->left);
    }
    if(node->right) {
        node->right = avl_balance_node(node->right);
    }

    int bf = avl_balance_factor(node);

    if(bf >= 2) {
        /* Left Heavy */

        if(avl_balance_factor(node->left) <= -1) {
            newroot = avl_rotate_leftright(node);
        } else {
            newroot = avl_rotate_leftleft(node);
        }

    } else if(bf <= -2) {
        /* Right Heavy */

        if(avl_balance_factor(node->right) >= 1) {
            newroot = avl_rotate_rightleft(node);
        } else {
            newroot = avl_rotate_rightright(node);
        }

    } else {
        /* This node is balanced -- no change. */

        newroot = node;
    }

    return(newroot);
}

void avl_balance(char_tree_t* tree) {
    char_info_t* newroot = NULL;

    newroot = avl_balance_node(tree->root);

    if(newroot != tree->root)  {
        tree->root = newroot;
    }
}

void avl_insert(char_tree_t* tree, char_info_t* info) {
    char_info_t* next = NULL;
    char_info_t* last = NULL;

    /* Check if there is a tree */
    if(tree==NULL){
        return;
    }

    /* Check if inserting node is valid */
    if(info==NULL){
        return;
    }

    /* Well, there must be a first case */
    if(tree->root == NULL) {
        tree->root = info;
    } else { /* Okay.  We have a root already.  Where do we put this? */
        next = tree->root;
        while(next != NULL) {
            last = next;
            if(info->code < next->code) {
                next = next->left;
            } else if(info->code > next->code) {
                next = next->right;
            } else if(info->code == next->code) { /* Have we already inserted this node? */
                /* This shouldn't happen. */
            }
        }
        if(info->code < last->code) {
            last->left = info;
        }
        if(info->code > last->code) {
            last->right = info;
        }

    }
    avl_balance(tree);
}

char_info_t* avl_find(char_tree_t* tree, int codepoint) {
    char_info_t* current = tree->root;
    while(current && current->code != codepoint) {
        if(codepoint > current->code) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return current;
}
