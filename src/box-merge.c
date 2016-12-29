#include "box-merge.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static const int dfa[][3] = {
    /* Initial, Final, Undefined  */
    {1        , 2    , 3}, /* 0 = Start     */
    {1        , 2    , 3}, /* 1 = Initial   */
    {1        , 2    , 3}, /* 2 = Final     */
    {1        , 2    , 3}  /* 3 = Undefined */
};

/* Concat two strings */
char* concat(const char* s1, const char* s2) {
    char* result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    if(result==NULL) {
        return NULL;
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/* Merge two boxes and form a new box, first box will be deallocated  */
static void expand_box(box_data_t* current, box_data_t* new_box, int current_count) {
    if(new_box==NULL) {
        fprintf(stderr,"Error: Merging box is uninitialized.\n");
        return;
    }
    if(current == NULL) {
        fprintf(stderr,"Error: Current box is uninitialized.\n");
        return;
    }
    if(current_count==0) {
        current->left = new_box->left;
        current->buttom = new_box->buttom;
        current->right = new_box->right;
        current->top = new_box->top;
        current->page = new_box->page;
        if(new_box->utf8) {
            current->utf8 = strdup(new_box->utf8);
            free(new_box->utf8);
            new_box->utf8=NULL;
        }
        return;
    }
    char* newStr = concat(current->utf8, new_box->utf8);
    if(current->utf8) {
        free(current->utf8);
        current->utf8=NULL;
    }
    if(new_box->utf8) {
        free(new_box->utf8);
        new_box->utf8=NULL;
    }
    current->utf8 = newStr;
    current->left = MIN(current->left,new_box->left);
    current->buttom = MIN(current->buttom,new_box->buttom);
    current->right = MAX(current->right,new_box->right);
    current->top = MAX(current->top,new_box->top);
}
void merge_boxses(const char* input_file, const char* output_file, char_tree_t* char_info) {
    printf("Reading box information from `%s'...\n",input_file);
    printf("Target box information file is `%s'...\n",output_file);
    FILE* f_input;
    FILE* f_output;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t total_boxes = 0;
    int current_state = 0;
    box_data_t* current_box = (box_data_t*)(malloc(sizeof(box_data_t)));
    current_box->utf8=NULL;
    box_data_t* box = NULL;
    f_input = fopen(input_file, "r");
    if(f_input == NULL) {
        fprintf(stderr,"Error: Unable to open `%s' for reading!\n",input_file);
        perror("Error");
        return;
    }
    /* Read all input lines into stack */
    stack_t* lines = stack_create();
    while((read = getline(&line, &len, f_input)) != -1) {
        if(read>1) {
            stack_push(lines,strdup(line));
        }
    }
    fclose(f_input);
    /* Open output file */
    f_output = fopen(output_file, "w");
    if(f_output == NULL) {
        fprintf(stderr,"Error: Unable to open `%s' for writing!\n",output_file);
        perror("Error");
        return;
    }
    int current_count = 0;
    while(!stack_is_empty(lines)) {
        line = stack_pop(lines);
        box = box_parse_line(line);
        free(line);
        if(box==NULL) {
            fprintf(stderr,"ERROR: Malformed input file! Reading next line...\n");
        } else {
            /* Calculate char code */
            int len = strlen(box->utf8);
            /* Move DFA */
            int code = codepoint(box->utf8,len);
            /* Fetch character class */
            char_info_t* info = avl_find(char_info, code);
            int move;
            if(info) {
                move = info->join_class;
            } else {
                move = 2;
            }
            current_state = dfa[current_state][move];
            //switch(current_state) {
            if(current_state==1) { /* Initial State */
                expand_box(current_box,box,current_count);
                current_count++;
            }
            if(current_state==2) { /* Final State */
                expand_box(current_box,box,current_count);
                fprintf(f_output,"%s %d %d %d %d %d\n",
                        current_box->utf8,
                        current_box->left,
                        current_box->buttom,
                        current_box->right,
                        current_box->top,
                        current_box->page);
                current_count = 0;
            }
            if(current_state==3) { /* Unknown State */
                if(current_count > 0) {
                    fprintf(f_output,"%s %d %d %d %d %d\n",
                            current_box->utf8,
                            current_box->left,
                            current_box->buttom,
                            current_box->right,
                            current_box->top,
                            current_box->page);
                    current_count = 0;
                }
                fprintf(f_output,"%s %d %d %d %d %d\n",
                        box->utf8,
                        box->left,
                        box->buttom,
                        box->right,
                        box->top,
                        box->page);
            }
            fflush(f_output);
            total_boxes++;

        }
    }
    fclose(f_output);
    printf("Total boxes read from `%s' is: %lu\n",input_file,total_boxes);
}
