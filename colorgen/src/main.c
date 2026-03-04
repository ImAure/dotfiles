#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "color.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char **argv) {
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

        // file_text[15] = 0;

        // lexer_t *lx = lx_create(file_text);
        //
        // for (int i = 0; i < 100; i++) {
        //        if (lx_next_token(lx).type == TOK_ERR) printf("cazzo...\n");
        // }
        // lx_destroy(lx);

        colorlist_t *list = ps_parse_colors(file_text);

        color_t c;
        c.type = RGB;
        strcpy(c.name, "ciao");
        c.as.rgb.r = 13;
        c.as.rgb.g = 14;
        c.as.rgb.b = 15;
        strcpy(c.as.aliasof.name, "ciaone");
        color_print(c);

        // colorlist_t *list = NULL;
        // colorlist_print(list);
        // list = colorlist_create();

        c.type = RGB;
        strcpy(c.name, "ciao");
        c.as.rgb.r = 13;
        c.as.rgb.g = 14;
        c.as.rgb.b = 15;
        colorlist_insert_color(list, c);

        c.type = ALIAS;
        strcpy(c.name, "ciaone");
        c.as.rgb.r = 13;
        c.as.rgb.g = 14;
        c.as.rgb.b = 15;
        strcpy(c.as.aliasof.name, "ciao");
        // colorlist_insert_color(list, c);
        //
        // colorlist_print(list);
}
