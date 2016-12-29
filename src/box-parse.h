#ifndef BOX_PARSE_H
#define BOX_PARSE_H

struct box_data {
    char* utf8;     /* null-terminated sequence of utf-8 encoded string */
    int left;
    int buttom;
    int right;
    int top;
    int page;
};
typedef struct box_data box_data_t;

box_data_t* box_parse_line(char* input);

#endif

