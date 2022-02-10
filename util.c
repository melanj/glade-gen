/*
Copyright (C) 2022 by Melan Jayasinghage <melan@apache.org>

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
 */
#include <ctype.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "util.h"

int is_leaf(xmlNode *node) {
    xmlNode *child = node->children;
    while (child) {
        if (child->type == XML_ELEMENT_NODE) return 0;

        child = child->next;
    }

    return 1;
}

char *strupr(char *s) {
    char *tmp = s;
    for (; *tmp; ++tmp) {
        *tmp = toupper((unsigned char) *tmp);
    }
    return s;
}

char *strrpc(char *str, char *orig, char *rep) {
    static char buffer[BLOCK];
    char *p;

    if (!(p = strstr(str, orig)))
        return str;

    strncpy(buffer, str, p - str);
    buffer[p - str] = '\0';

    sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));

    return buffer;
}
