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
#include "stack.h"

stack_t* stack_create() {
    /* Create a stack and set everything to the default values. */
    stack_t* stack = (stack_t*) malloc(sizeof(stack_t*));
    if(stack == NULL) {
        return NULL;
    }

    stack->count = 0;
    stack->top = NULL;

    return stack;
}

void stack_destroy(stack_t* s) {
    stack_clean(s);
    free(s);
}

void stack_clean(stack_t* s) {
    while(!stack_is_empty(s)) {
#ifdef allocated_item_type
        item_t item = stack_pop(s);
        free(item);
#else
        stack_pop(s);
#endif
    }
}

int stack_is_empty(stack_t* s) {
    return s->top == NULL ? 1 : 0;
}

size_t stack_size(stack_t* s) {
    return s->count;
}

item_t stack_top(stack_t* s) {
    return s->top->item;
}

int stack_push(stack_t* s, item_t item) {
    stack_node_t* newNode = (stack_node_t*) malloc(sizeof *newNode);
    if(newNode == NULL) {
        return 0;
    }

    newNode->item = item;
    newNode->next = s->top;
    s->top = newNode;

    s->count += 1;
    return 1;
}

item_t stack_pop(stack_t* stack) {
    stack_node_t* oldTop;
    item_t item;

    if(stack->top == NULL) {
        return 0;    /** @todo Make a better way to return this error. **/
    }

    oldTop = stack->top;
    item = oldTop->item;
    stack->top = oldTop->next;
    free(oldTop);
    oldTop = NULL;

    stack->count -= 1;
    return item;
}
