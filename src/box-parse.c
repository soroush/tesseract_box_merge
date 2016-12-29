#include "box-parse.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

box_data_t* box_parse_line(char* input) {
    /* Check input validity */
    if(input==NULL) {
        return NULL;
    }
    char* string = NULL;
    char* left = NULL;
    char* buttom = NULL;
    char* right = NULL;
    char* top = NULL;
    char* type = NULL;
    /* Check if first character is space, if so tokenizer will not work */
    int is_space = 0;
    if(input[0]==' ') {
        is_space = 1;
    }
    if(is_space == 0) {
        string = strtok(input," ");
        left = strtok(NULL," ");
    } else {
        string = " ";
        left = strtok(input," ");
    }
    buttom = strtok(NULL," ");
    right = strtok(NULL," ");
    top = strtok(NULL," ");
    type = strtok(NULL," ");
    if(string == NULL ||
            left == NULL || buttom == NULL ||
            right == NULL || top == NULL ||
            type == NULL) {
        return NULL;
    }
    box_data_t* info = malloc(sizeof(box_data_t));
    info->utf8 = strdup(string);
    info->left = (int)(strtoul(left,NULL,10));
    info->buttom = (int)(strtoul(buttom,NULL,10));
    info->right = (int)(strtoul(right,NULL,10));
    info->top = (int)(strtoul(top,NULL,10));
    info->page = (int)(strtoul(type,NULL,10));
    return info;
}

