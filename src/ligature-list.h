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

#ifndef LIGATURE_LIST_H_INCLUDED
#define LIGATURE_LIST_H_INCLUDED

#include <stdlib.h>


struct node {
    size_t reference_count;     /* Number of previous occurances */
    char* structure;            /* UTF string of structure */
    struct node* next;
};

struct ligature_list {
    struct node* head;
    struct node* tail;
    size_t size;
};

typedef struct node node_t;
typedef struct ligature_list ligature_list_t;

ligature_list_t* list_create();
int add(ligature_list_t* ligature_list, const char* structure, size_t max);

#endif
