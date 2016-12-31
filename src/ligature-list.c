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

#include <stdlib.h>
#include <string.h>
#include "ligature-list.h"


ligature_list_t* list_create() {
    ligature_list_t* list = (ligature_list_t*)malloc(sizeof(ligature_list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/*
 * Adds a new structure to the ligature list
 * return value:
 *   0 : Reapeated structure
 *   1 : New structure
 */

int add(ligature_list_t* list, const char* structure, size_t max) {
    struct node* current = list->head;
    while(current) {
        if(strcmp(current->structure, structure)==0) {
            /* Structure has been seen before */
            if(current->reference_count < max) {
                ++current->reference_count;
            }
            return 0;
        }
        current = current->next;
    }
    /* First encounter of such structure */
    node_t* newItem = (node_t*)(malloc(sizeof(node_t)));
    newItem->reference_count = 0;
    newItem->structure = strdup(structure);
    list->tail->next = newItem;
    list->tail = newItem;
    ++list->size;
    return 1;
}
