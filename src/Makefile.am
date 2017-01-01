# This file is part of boxmerge.
#
# boxmerge is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# boxmerge is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with boxmerge.  If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS = \
    merge_boxes \
    extract_ligatures

merge_boxes_SOURCES = \
    common.h \
    common.c \
    stack.h \
    stack.c \
    char-tree.h \
    char-tree.c \
    unicode-utils.h \
    unicode-utils.c \
    ucd-parse.h \
    ucd-parse.c \
    box-parse.h \
    box-parse.c \
    box-merge.h \
    box-merge.c \
    embedded-ucd.h \
    main-merge-boxes.c

extract_ligatures_SOURCES = \
    common.h \
    common.c \
    char-tree.h \
    char-tree.c \
    unicode-utils.h \
    unicode-utils.c \
    ucd-parse.h \
    ucd-parse.c \
    ligature-list.h \
    ligature-list.c \
    ligature-extract.h \
    ligature-extract.c \
    main-extract-ligatures.c
