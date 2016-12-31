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

#ifndef LIGATURE_EXTRACT_H_INCLUDE
#define LIGATURE_EXTRACT_H_INCLUDE

#include "ligature-list.h"
#include "char-tree.h"

void ligature_extract(const char* input_file,
                      const char* output_file,
                      ligature_list_t* ligature_info,
                      char_tree_t *char_info);

#endif
