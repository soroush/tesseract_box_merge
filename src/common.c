#include "common.h"
#include <stddef.h>

void remove_spaces(char* source) {
    if(source==NULL) {
        return;
    }
    char* i = source;
    char* j = source;
    while(*j != 0) {
        *i = *j++;
        if(*i != ' ' && *i != '\n') {
            i++;
        }
    }
    *i = 0;
}

