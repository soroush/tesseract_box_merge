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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "unicode-utils.h"
#include "ucd-parse.h"

int main(int argc, char* argv[]) {
    char* s1     = "\xD9\x85\xD8\xAA\xD9\x86";   /* Matn */
    /* char* s1_t[] = {"\xD9\x85\xD8\xAA\xD9\x86"}; /\* Matn *\/ */
    /* char* s2   = "\xD8\xB3\xD9\x84\xD8\xA7\xD9\x85"; /\* Salam *\/ */
    /* char* s2_l[] = {"\xD8\xB3\xD9\x84\xD8\xA7",      /\* Sala *\/ */
    /*                 "\xD9\x85"                       /\* Mim *\/ */
    /*                }; */
    /* char* s3     = "\xD9\x85\xD9\x86\xD8\xAD\xD9\x86\xDB\x8C"; /\* Monhani *\/ */
    /* char* s3_l[] = {"\xD9\x85\xD9\x86\xD8\xAD\xD9\x86\xDB\x8C"}; /\* Monhani *\/ */
    /* char* s4     = "\xD8\xA7\xD8\xB7\xD9\x85\xDB\x8C\xD9\x86\xD8\xA7\xD9\x86"; /\* Etminan *\/ */
    /* char* s4_l[] = {"\xD8\xB7", /\* Alef *\/ */
    /*                 "\xD8\xB7\xD9\x85\xDB\x8C\xD9\x86\xD8\xA7", /\* 'tmina *\/ */
    /*                 "\xD9\x86" /\* Etminan *\/ }; */
    initialize_global_tree(1);
    printf("%s\n","Starting...");
    char* l = strtok_l(s1);
    while(l){
        printf("%s %s\n\n\n",s1,l);
        l = strtok_l(NULL);
    }
    exit(EXIT_SUCCESS);
}

