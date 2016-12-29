#include "ucd-parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char_info_t* parse_line(char* input) {
    char_info_t* info = malloc(sizeof(char_info_t));
    char* code = NULL;
    char* name = NULL;
    char* type = NULL;
    code = strtok(input,";");
    name = strtok(NULL,";");
    type = strtok(NULL,";");
    remove_spaces(type);
    if(code == NULL || name == NULL || type == NULL) {
        return NULL;
    }
    switch(type[0]) {
        case 'D':
        case 'L':
        case 'T':
            info->join_class = 0;
            break;
        case 'R':
        case 'C':
            info->join_class = 1;
            break;
        case 'U':
            info->join_class = 2;
            break;
        default:
            info->join_class = 2;
            break;
    }
    info->code = (int)(strtoul(code,NULL,16));
    return info;
}

int codepoint(const char* u, size_t l) {
    if(l<1) {
        return -1;
    }
    unsigned char u0 = u[0];
    if(u0>=0   && u0<=127) {
        return u0;
    }
    if(l<2) {
        return -1;
    }
    unsigned char u1 = u[1];
    if(u0>=192 && u0<=223) {
        return (u0-192)*64 + (u1-128);
    }
    if(u[0]==0xed && (u[1] & 0xa0) == 0xa0) { //code points, 0xd800 to 0xdfff
        return -1;
    }
    if(l<3) {
        return -1;
    }
    unsigned char u2 = u[2];
    if(u0>=224 && u0<=239) {
        return (u0-224)*4096 + (u1-128)*64 + (u2-128);
    }
    if(l<4) {
        return -1;
    }
    unsigned char u3 = u[3];
    if(u0>=240 && u0<=247) {
        return (u0-240)*262144 + (u1-128)*4096 + (u2-128)*64 + (u3-128);
    }
    return -1;
}


char_tree_t* generate_ucd_data(const char* database) {
    printf("Reading character join classes from `%s'...\n",database);
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(database, "r");
    if(fp == NULL) {
        fprintf(stderr,"Error: Unable to open `%s' for reading!\n",database);
        perror("Error");
        return NULL;
    }
    char_tree_t* tree = avl_create_tree();
    size_t total_chars = 0;
    while((read = getline(&line, &len, fp)) != -1) {
        if(read>1) {
            if(line[0]!='#') {
                char_info_t* info = parse_line(line);
                if(info==NULL) {
                    fprintf(stderr,"ERROR: Malformed input file! Reading next line...\n");
                    continue;
                } else {
                    avl_insert(tree,info);
                }
                total_chars++;
            }
        }
    }
    fclose(fp);
    if(line) {
        free(line);
    }
    printf("Total characters read from UCD: %lu\n",total_chars);
    return tree;
}


