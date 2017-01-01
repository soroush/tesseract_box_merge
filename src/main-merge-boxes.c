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
#include "common.h"
#include "ucd-parse.h"
#include "box-merge.h"

void print_usage() {
    fprintf(stderr, "Usage: merge_boxes -i input_file -o output_file -u ucd_database\n");
}

int main(int argc, char* argv[]) {
    char* ucd_database = NULL;
    char* input_box_file = NULL;
    char* output_box_file = NULL;
    int index;
    int c;
    opterr = 0;
    if(argc!=7) {
        print_usage();
        exit(EXIT_FAILURE);
    }
    while((c = getopt(argc, argv, "u:i:o:")) != -1) {
        switch(c) {
            case 'u':
                ucd_database = optarg;
                break;
            case 'i':
                input_box_file = optarg;
                break;
            case 'o':
                output_box_file = optarg;
                break;
            case '?':
                if(optopt == 'u' || optopt == 'i' || optopt == 'o') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if(isprint(optopt)) {
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                } else
                    fprintf(stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                return 1;
            default:
                abort();
        }
    }
    int error = 0;
    if(input_box_file==NULL) {
        fprintf(stderr, "ERROR: No input file specified!\n");
        error = 1;
    }
    if(output_box_file==NULL) {
        fprintf(stderr, "ERROR: No output file specified!\n");
        error = 1;
    }
    if(ucd_database==NULL) {
        fprintf(stderr, "ERROR: No UCD Database file specified!\n");
        error = 1;
    }
    if(error==1) {
        print_usage();
        exit(EXIT_FAILURE);
    }
    generate_ucd_data(ucd_database);
    merge_boxses(input_box_file, output_box_file);
    exit(EXIT_SUCCESS);
}
