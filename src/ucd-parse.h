#ifndef BOX_MERGE_UCD_PARSE
#define BOX_MERGE_UCD_PARSE

#include <stddef.h>
#include "char-tree.h"

int codepoint(const char* u, size_t l);
char_tree_t* generate_ucd_data(const char* database);

#endif /* BOX_MERGE_UCD_PARSE */

