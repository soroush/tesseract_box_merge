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
