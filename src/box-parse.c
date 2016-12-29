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

