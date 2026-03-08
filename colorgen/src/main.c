#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "color.h"
#include "parser.h"

// #define MAIN_DEBUG

int main(int argc, char **argv) {
        printf("\n===== EXECUTION START =====\n");
        if (argc != 2) {
                fprintf(stderr, "Wrong number of arguments.\nUsage: %s path/to/file", argv[0]);
                return 1;
        }

        FILE *fp;
        size_t file_size;
        char *file_text;

        fp = fopen(argv[1], "r");
        if (fp == NULL) {
                perror("Could not read file");
                return 1;
        }

        /* get file size */
        fseek(fp, 0, SEEK_END);
        file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        printf("File size is %zu\n", file_size);

        /* allocate memory for text and load file */
        file_text = malloc(file_size + 1);
        if (file_text == NULL) {
                perror("Could not load file");
                fclose(fp);
                return 1;
        }
        fread(file_text, file_size, 1, fp);
        file_text[file_size] = 0;
        fclose(fp);

        colorlist_t *list = ps_parse_palette(file_text);
        colorlist_print(list);
        colorlist_destroy(list);




#ifdef MAIN_DEBUG
        if (!list) list = colorlist_create();
        color_t c;
        c.type = RGB;
        strcpy(c.name, "rosso");
        c.as.rgb.r = 250;
        c.as.rgb.g = 11;
        c.as.rgb.b = 12;
        colorlist_insert_color(list, c);

        c.type = ALIAS;
        strcpy(c.name, "sangue");
        strcpy(c.as.aliasof.name, "lu");
        colorlist_insert_color(list, c);

        c.type = ALIAS;
        strcpy(c.name, "blu");
        strcpy(c.as.aliasof.name, "rosso");
        colorlist_insert_color(list, c);

        colorlist_print(list);

        printf("Resolving aliases...\n");
        colorlist_resolve_aliases(list);

        colorlist_print(list);

        printf("le rore?\n");
        c.type = ALIAS;
        strcpy(c.name, "carlo");
        strcpy(c.as.aliasof.name, "luigi");
        colorlist_insert_color(list, c);
        c.type = ALIAS;
        strcpy(c.name, "luigi");
        strcpy(c.as.aliasof.name, "carlo");
        colorlist_insert_color(list, c);
        colorlist_resolve_aliases(list);
        colorlist_print(list);
        colorlist_destroy(list);
#endif
}
