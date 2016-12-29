#ifndef CHARACTER_TREE_AVL_H
#define CHARACTER_TREE_AVL_H

#include "common.h"

struct char_tree {
    struct char_info* root;
};
typedef struct char_tree char_tree_t;

/* Create a new AVL tree. */
char_tree_t* avl_create_tree();

/* Initialize a new node. */
char_info_t* avl_create_node();

/* Find the height of an AVL node recursively */
int avl_node_height(char_info_t* node);

/* Find the balance of an AVL node */
int avl_balance_factor(char_info_t* node);

/* Left Left Rotate */
char_info_t* avl_rotate_leftleft(char_info_t* node);

/* Left Right Rotate */
char_info_t* avl_rotate_leftright(char_info_t* node);

/* Right Left Rotate */
char_info_t* avl_rotate_rightleft(char_info_t* node);

/* Right Right Rotate */
char_info_t* avl_rotate_rightright(char_info_t* node);

/* Balance a given node */
char_info_t* avl_balance_node(char_info_t* node);

/* Balance a given tree */
void avl_balance(char_tree_t* tree);

/* Insert a new node. */
void avl_insert(char_tree_t* tree, char_info_t* info);

/* Find the node containing a given value */
char_info_t* avl_find(char_tree_t* tree, int codepoint);

#endif
