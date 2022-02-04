# Copyright (C) 2022 by Melan Jayasinghage <melan@apache.org>
#
# Permission to use, copy, modify, and/or distribute this software for any purpose
# with or without fee is hereby granted.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
# FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
# OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
# TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
# THIS SOFTWARE.

CC = gcc
CFLAGS = `xml2-config --cflags`
LDFLAGS = `xml2-config --libs`

all : gladegen

gladegen : main.o
	$(CC) -o gladegen main.o $(LDFLAGS)

main.o : main.c
	$(CC) $(CFLAGS) -c main.c

clean :
	rm gladegen *.o
