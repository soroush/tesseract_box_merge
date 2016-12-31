/*
 * This file is part of boxmerge.
 *
 * boxmerge is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * boxmerge is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with boxmerge.  If not, see <http://www.gnu.org/licenses/>.
 */

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
