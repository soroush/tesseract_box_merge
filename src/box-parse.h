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

