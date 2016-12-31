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

#include "ligature-extract.h"
#include "common.h"
#include "ucd-parse.h"
#include <stdio.h>

/* void ligature_extract(const char* input_file, */
/*                       const char* output_file, */
/*                       ligature_list_t* ligature_info, */
/*                       char_tree_t* char_info) { */
/*     FILE* f_input; */
/*     FILE* f_output; */
/*     long  total_chars=0;     /\* Total number of characters, in bytes *\/ */
/*     long  total_unicode=0;   /\* Total number of unicode characters *\/ */
/*     long  repeat_count=0;    /\* Number of repeated unicode characters *\/ */
/*     int new_structure=0; */
/*     char buffer[] = { */
/*         '\0','\0','\0','\0', */
/*         '\0','\0','\0','\0', */
/*     }; */
/*     f_input = fopen(input_file, "r"); */
/*     if(f_input == NULL) { */
/*         fprintf(stderr,"Error: Unable to open `%s' for reading!\n",input_file); */
/*         perror("Error"); */
/*         return; */
/*     } */
/*     /\* Open output file *\/ */
/*     f_output = fopen(output_file, "w"); */
/*     if(f_output == NULL) { */
/*         fprintf(stderr,"Error: Unable to open `%s' for writing!\n",output_file); */
/*         perror("Error"); */
/*         return; */
/*     } */
/*     size_t line_len=0;            /\* Length of unicode char in bytes *\/ */
/*     size_t read_bytes; */
/*     char* line = NULL; */
/*     while((read_bytes = getline(&line, &line_len, input_file)) != -1) { */
/*         char* word = strtok(line," "); */
/*         while(word != NULL) { */
/*             size_t ligature_count = 0; */
/*             char** ligatures = strtok_l(word); */
/*             int is_new_ligature = 0; */
/*             while (ligature_count!=0) { */
/*                 ligature_count--; */
/*                 if(add(ligature_info,ligatures[ligature_count],20)==1){ */
/*                     is_new_ligature=1; */
/*                 } */
/*             } */
/*             if(is_new_ligature){ */
/*                 /\* Write the word to output file *\/ */
/*             } */
/*             word = strtok(NULL," "); */
/*         } */
/*     } */
/* } */
