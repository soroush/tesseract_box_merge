#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdlib.h>

#define item_t char*
#define allocated_item_type

struct stack_node {
    item_t item;             /** The data of this node. **/
    struct stack_node* next; /** The next node (the one below the top). **/
};

struct stack {
    size_t count;            /** The number of items in the stack. **/
    struct stack_node* top;  /** The top item of the stack. **/
};

typedef struct stack_node stack_node_t;
typedef struct stack stack_t;

stack_t *stack_create();
void stack_destroy(stack_t *s);
void stack_clean(stack_t *s);
int stack_is_empty(stack_t *s);
size_t stack_size(stack_t *s);
item_t stack_top(stack_t *s);
int stack_push(stack_t *s, item_t i);
item_t stack_pop(stack_t *s);

#endif
