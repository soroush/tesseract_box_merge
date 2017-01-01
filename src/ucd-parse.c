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

#include "ucd-parse.h"
#include <stdlib.h>
#include <stdio.h>
#include "embedded-ucd.h"
#include <string.h>

//extern unsigned char* __src_ArabicShaping_txt;
//extern unsigned int __src_ArabicShaping_txt_len ;

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


void generate_ucd_data(const char* database) {
    printf("Reading character join classes from `%s'...\n",database);
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    if(database){
        fp = fopen(database, "r");
    }else {
        initialize_global_tree(1);
        fp = fmemopen(__src_ArabicShaping_txt,__src_ArabicShaping_txt_len,"r");
    }
    if(fp == NULL) {
        fprintf(stderr,"Error: Unable to open `%s' for reading!\n",database);
        perror("Error");
        return;
    }
    size_t total_chars = 0;
    while((read = getline(&line, &len, fp)) != -1) {
        if(read>1) {
            if(line[0]!='#') {
                char_info_t* info = parse_line(line);
                if(info==NULL) {
                    fprintf(stderr,"ERROR: Malformed input file! Reading next line...\n");
                    continue;
                } else {
                    avl_insert(global_char_info,info);
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
}
