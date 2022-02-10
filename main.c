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
#include <stdio.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "util.h"


void find_widgets(xmlNode *node, STRBUF *declare_buf, STRBUF *init_buf, STRBUF *signal_buf) {
    while (node) {
        if (node->type == XML_ELEMENT_NODE) {

            if (!is_leaf(node)) {
                char *id = (char *) xmlGetProp(node, "id");
                char *class = (char *) xmlGetProp(node, "class");
                if (id != NULL && class != NULL) {

                    declare_buf->append = declare_buf->buffer + declare_buf->append_len;
                    declare_buf->append_len += sprintf(declare_buf->append, "%s *%s;\n", class, id);
                    if ((declare_buf->len - declare_buf->append_len) < BLOCK) {
                        declare_buf->len += BLOCK;
                        declare_buf->buffer = realloc(declare_buf->buffer, declare_buf->len);
                    }

                    init_buf->append = init_buf->buffer + init_buf->append_len;
                    init_buf->append_len += sprintf(init_buf->append,
                                                    "\t%s = %s(gtk_builder_get_object(builder, \"%s\"));\n", id,
                                                    strrpc(strupr(class), "GTK", "GTK_"), id);
                    if ((init_buf->len - init_buf->append_len) < BLOCK) {
                        init_buf->len += BLOCK;
                        init_buf->buffer = realloc(init_buf->buffer, init_buf->len);
                    }

                    xmlNode *child = node->children;
                    while (child) {
                        if (child->type == XML_ELEMENT_NODE && !xmlStrcmp(child->name, (const xmlChar *) "signal")) {
                            signal_buf->append = signal_buf->buffer + signal_buf->append_len;
                            signal_buf->append_len += sprintf(signal_buf->append, "void %s (%s *e){\n\n}\n",
                                                              xmlGetProp(child, "handler"), xmlGetProp(node, "class"));
                            if ((signal_buf->len - signal_buf->append_len) < BLOCK) {
                                signal_buf->len += BLOCK;
                                signal_buf->buffer = realloc(signal_buf->buffer, signal_buf->len);
                            }
                        }
                        child = child->next;
                    }

                }
                xmlFree(id);
                xmlFree(class);
            }
        }
        find_widgets(node->children, declare_buf, init_buf, signal_buf);
        node = node->next;
    }
}

void generate_code(char *filename, char *declare_buf, char *init_buf, char *signal_buf) {
    char *target_file = strrpc(strrpc(filename, ".xml", ".c"), ".glade", ".c");
    FILE *fPtr = fopen(target_file, "w");

    if (fPtr == NULL) {
        printf("Unable to create file.\n");
    }
    //TODO: implement proper template based code generation
    fputs("//generate from ", fPtr);
    fputs(filename, fPtr);
    fputs("\n", fPtr);
    fputs("#include <signal.h>\n", fPtr);
    fputs("#include <gtk/gtk.h>\n", fPtr);
    fputs("\n", fPtr);
    fputs("//widget declarations\n", fPtr);
    fputs(declare_buf, fPtr);
    fputs("//builder declaration\n", fPtr);
    fputs("GtkBuilder *builder;\n", fPtr);
    fputs("\n", fPtr);
    fputs("int main(int argc, char *argv[]) {\n\n", fPtr);
    fputs("\tgtk_init(&argc, &argv);\n\n", fPtr);
    fputs("\tbuilder = gtk_builder_new_from_file (\"", fPtr);
    fputs(filename, fPtr);
    fputs("\");\n", fPtr);
    fputs("\tgtk_builder_connect_signals(builder, NULL);\n\n", fPtr);
    fputs("\t//widget initialization\n", fPtr);
    fputs(init_buf, fPtr);
    fputs("\n", fPtr);
    fputs("\tg_signal_connect(window, \"destroy\", G_CALLBACK(gtk_main_quit), NULL);\n", fPtr);
    fputs("\tgtk_widget_show(GTK_WIDGET(window));\n", fPtr);
    fputs("\tgtk_main();\n\n", fPtr);
    fputs("\treturn EXIT_SUCCESS;\n", fPtr);
    fputs("}\n", fPtr);
    fputs("\n", fPtr);
    fputs("//signals\n", fPtr);
    fputs(signal_buf, fPtr);
    fclose(fPtr);
    printf("generated %s\n", target_file);
}

int main(int argc, char **argv) {

    if (argc <= 1) {
        printf("Usage: %s <Glade XML file> \n", argv[0]);
        return (0);
    }

    STRBUF declare_buf;
    declare_buf.len = BLOCK;
    declare_buf.buffer = (char *) malloc(declare_buf.len);
    declare_buf.append_len = 0;
    declare_buf.append = declare_buf.buffer;

    STRBUF init_buf;
    init_buf.len = BLOCK;
    init_buf.buffer = (char *) malloc(init_buf.len);
    init_buf.append_len = 0;
    init_buf.append = init_buf.buffer;

    STRBUF signal_buf;
    signal_buf.len = BLOCK;
    signal_buf.buffer = (char *) malloc(signal_buf.len);
    signal_buf.append_len = 0;
    signal_buf.append = signal_buf.buffer;

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("Could not parse the XML file");
    }

    root_element = xmlDocGetRootElement(doc);
    find_widgets(root_element, &declare_buf, &init_buf, &signal_buf);

    generate_code(argv[1], declare_buf.buffer, init_buf.buffer, signal_buf.buffer);

    xmlFreeDoc(doc);
    xmlCleanupParser();
}

