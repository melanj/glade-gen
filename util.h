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
#ifndef GLADEGEN_UTIL_H
#define GLADEGEN_UTIL_H
#define BLOCK 255

typedef struct {
    size_t len;
    char *buffer;
    int append_len;
    char *append;
} STRBUF;

int is_leaf(xmlNode *node);
char *strupr(char *s);
char *strrpc(char *str, char *orig, char *rep);

#endif //GLADEGEN_UTIL_H
