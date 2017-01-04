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

#include <string.h>
#include "char-tree.h"
#include "unicode-utils.h"

int codepoint(const char* u, size_t l) {
    if(l<1) {
        return -1;
    }
    unsigned char u0 = u[0];
    if(u0>=0   && u0<=127) {
        return u0;
    }
    if(l<2) {
        return -1;
    }
    unsigned char u1 = u[1];
    if(u0>=192 && u0<=223) {
        return (u0-192)*64 + (u1-128);
    }
    /* code points, 0xd800 to 0xdfff */
    if(u[0]==0xed && (u[1] & 0xa0) == 0xa0) {
        return -1;
    }
    if(l<3) {
        return -1;
    }
    unsigned char u2 = u[2];
    if(u0>=224 && u0<=239) {
        return (u0-224)*4096 + (u1-128)*64 + (u2-128);
    }
    if(l<4) {
        return -1;
    }
    unsigned char u3 = u[3];
    if(u0>=240 && u0<=247) {
        return (u0-240)*262144 + (u1-128)*4096 + (u2-128)*64 + (u3-128);
    }
    return -1;
}

char* strtok_l(const char* src) {
    static char unichar[4]= {'\0','\0','\0','\0'};
    static char* buffer = NULL;
    static char* oldsrc = NULL;
    static size_t current = 0;
    static size_t src_current = 0;
    static size_t len = 0;
    int unicode = 0;
    size_t start = 0;
    if(src==NULL) {
        if(oldsrc==NULL) {
            /* ERROR */
            return NULL;
        } else {
            start = current;
        }
    } else {
        if(oldsrc) {
            free(oldsrc);
        }
        if(buffer) {
            free(buffer);
        }
        len = strlen(src);
        buffer = malloc(sizeof(char)*2*len+1);
        oldsrc = strdup(src);
        src_current = 0;
        current = 0;
        start = 0;
    }
    int current_state = 0;
    /* Read each byte from string untill either string ends, or
     * a ligature is found
     */
    while(current_state<2 && src_current<len) {
        /* A common case: character is in ASCII table */
        if((oldsrc[src_current]& 0x80)==0x00) {
            /* Since there is no single-byte unicode char that joins
             * to other characters, there is no need to search the
             * avl tree. */
            buffer[current] = oldsrc[src_current];
            buffer[current+1] = '\0';
            /* Jump over the trailing '\0' char. */
            current += 2;
            src_current += 1;
        }
        /* Most common case: character is two-byte and probably is
         * in Arabic range. */
        else if((oldsrc[src_current] & 0xE0)==0xC0) {
            /* Checking validity of second byte is skipped intentionally,
             * to increase performance. */
            buffer[current] = oldsrc[src_current];
            buffer[current+1] = oldsrc[src_current+1];
            unichar[0] = oldsrc[src_current];
            unichar[1] = oldsrc[src_current+1];
            unichar[3] = '\0';
            unicode = codepoint(unichar,2);
            char_info_t* info = avl_find(global_char_info,unicode);
            int move = 0;
            if(info==NULL) {
                /* There is no info for that char, so it must be non-joining */
                move = 2;
            } else {
                move = info->join_class;
            }
            current_state = dfa[current_state][move];
            current += 2;
            src_current += 2;
        }
    }
    buffer[current]='\0';
    current++;
    if(src_current==len) {
        return NULL;
    }
    return &(buffer[start]);
}

//    char c0;
//    char c1;
//    char c2;
//    char c3;
//    if(c0==EOF) {
//        len = 0;
//        buf[0]='\0';
//    } else if((c0 & 0x80)==0x00) {
//        len=1;
//        buf[0]=c0;
//        buf[1]='\0';
//    } else if((c0 & 0xE0)==0xC0) {
//        c1 = fgetc(file);
//        if((c1 & 0xC0)==0x80) {
//            len=2;
//            buf[0]=c0;
//            buf[1]=c1;
//            buf[2]='\0';
//        } else {
//            /* ERROR */
//        }
//    } else if((c0 & 0xF0)==0xE0) {
//        c1 = fgetc(file);
//        c2 = fgetc(file);
//        if((c1 & 0xC0)==(c2 & 0xC0)==0x80) {
//            len=3;
//            buf[0]=c0;
//            buf[1]=c1;
//            buf[2]=c2;
//            buf[3]='\0';
//        } else {
//            /* ERROR */
//        }
//    } else if((c0 & 0xF8)==0xF0) {
//        c1 = fgetc(file);
//        c2 = fgetc(file);
//        c3 = fgetc(file);
//        if((c1 & 0xC0)==(c2 & 0xC0)==(c3 & 0xC0)==0x80) {
//            len=4;
//            buf[0]=c0;
//            buf[1]=c1;
//            buf[2]=c2;
//            buf[3]=c3;
//            buf[4]='\0';
//        } else {
//            /* ERROR */
//        }
//    }
