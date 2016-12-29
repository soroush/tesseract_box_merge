#ifndef BOX_MERGE_COMMON_H
#define BOX_MERGE_COMMON_H

struct char_info {
    struct char_info* left;
    struct char_info* right;
    int code;       /* Code point of character */
    int join_class; /* 0=Dual, 1=Right, 2=None */
};
typedef struct char_info char_info_t;

void remove_spaces(char* source);

#endif /* BOX_MERGE_COMMON_H */
