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

#ifndef UNICODE_UTILS_H
#define UNICODE_UTILS_H

#include <stddef.h>

static const int dfa[][3] = {
    /* Initial, Final, Undefined  */
    {1        , 2    , 3        }, /* 0 = Start     */
    {1        , 2    , 3        }, /* 1 = Initial   */
    {1        , 2    , 3        }, /* 2 = Final     */
    {1        , 2    , 3        }  /* 3 = Undefined */
};

int codepoint(const char* u, size_t l);
char* strtok_l(const char *src);

#endif /* UNICODE_UTILS_H */
