#include "rgba.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"


typedef struct _token {
        char    text[NAME_MAX_LEN + 1];
        uint8_t type;
        uint16_t refcount;
} token_t;

int main(int argc, char **argv) {
        printf("ciao!\n");

        if (argc != 2) {
                fprintf(stderr, "Wrong number of arguments.\nUsage: %s path/to/file", argv[0]);
                return 1;
        }

        FILE *fp;
        size_t file_size;
        char *text;

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
        text = malloc(file_size + 1);
        if (text == NULL) {
                perror("Could not load file");
                fclose(fp);
                return 1;
        }
        fread(text, file_size, 1, fp);
        text[file_size] = 0;
        fclose(fp);
        printf("qua ci siamo\n");

        psParse(text);








        return 0;

}

