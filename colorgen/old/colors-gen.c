#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define STRLEN 1024
#define MAX_NAME_LEN 128
#define RGB_SIZE 3
#define RGBA_SIZE 4
#define RGBA_DIGITS 8
#define NAME_DELIMITER '\"'
#define HEX_DELIMITER '#'
#define UCHAR_MAX 255
#define DEFAULT_LIST_LEN 16

typedef struct _parser {
    char *body;
    char *current;
} parser_t;

typedef struct _rgbacolor {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    unsigned char alpha;
    char name[MAX_NAME_LEN];
} rgbacolor_t;

typedef struct _rgbalist {
    size_t len;
    size_t count;
    rgbacolor_t *element;
} rgbalist_t;



/*====================== COLOR LIST FUNCTIONS ====================*/

rgbalist_t *rgbalist_create(size_t len) {
    if (len == 0) {
        fprintf(stderr, "Cannot create list with len %zu. Length must be an unsigned (positive) integer.", len);
        return NULL;
    }
    rgbalist_t *list;

    list = malloc(sizeof(rgbalist_t));
    if (list == NULL) {
        perror("Could not create new list");
        return NULL;
    }

    list->len = len;
    list->count = 0;
    list->element = malloc((sizeof(rgbacolor_t)) * len);
    if (list->element == NULL) {
        perror("Could not create new list, no space for elements");
        return NULL;
    }

    return list;
}

int rgbalist_insert(rgbalist_t *list, rgbacolor_t *color) {
    if (list == NULL || color == NULL) {
        fprintf(stderr, "List or color does not exist\n");
        return 1;
    }
    if (list->element == NULL || list->len == 0) {
        fprintf(stderr, "Invalid list, 0 elements or null pointer");
        return 1;
    }
    size_t newsize;

    if (list->count == list->len) {
        newsize = list->len * 2 * sizeof(rgbacolor_t);
        list->element = realloc(list->element, newsize);
        list->len *= 2;

        if (list->element == NULL) {
            fprintf(stderr, "cazzo...");
            return -1;
        }
    }

    list->element[list->count++] = *color;
    return 0;
}


unsigned char hextouc(char *stream) {
    if (stream == NULL) return 0;
    if (!(isxdigit(stream[0]) && isxdigit(stream[1]))) return UCHAR_MAX;

    char value = 0;
    if (stream[0] >= '0' && stream[0] <= '9') value += (stream[0] - '0') * 16;
    else if (stream[0] >= 'a' && stream[0] <= 'f') value += (stream[0] - 'a' + 10) * 16;
    else if (stream[0] >= 'A' && stream[0] <= 'F') value += (stream[0] - 'A' + 10) * 16;

    if (stream[1] >= '0' && stream[1] <= '9') value += (stream[1] - '0');
    else if (stream[1] >= 'a' && stream[1] <= 'f') value += (stream[1] - 'a' + 10);
    else if (stream[1] >= 'A' && stream[1] <= 'F') value += (stream[1] - 'A' + 10);

    return value;
}

/*============================= PARSING ============================*/
int parse_spaces(parser_t *p) {
    if (p == NULL) { return 1; }
    if (p->body == NULL || p->current || NULL) { return 1; }
    if (p->current[0] == '\0') return 1;
    while (isspace(p->current[0])) { p->current++; }
    return 0;
}


int parse_name(parser_t *p, rgbacolor_t *c) {
    if (p == NULL || c == NULL) return 1;
    int i = 0;
    p->current++;

    while (
        (isalnum(p->current[0]) ||
        p->current[0] == '-' ||
        p->current[0] == '_') &&
        (i < MAX_NAME_LEN - 1)
    ) {
        c->name[i++] = *p->current++;
        /* printf("ho letto %c\n", c->name[i]); */
    }

    c->name[i] = '\0';
    if (*p->current == '\"') p->current++;
    return 0;
}

int parse_hex(parser_t *p, rgbacolor_t *c) {
    if (p == NULL || c == NULL) { return 1; }
    int i, good_counts;
    char buffer[RGBA_DIGITS + 1];
    p->current++;

    i = 0;
    while (isxdigit(p->current[0])) {
        buffer[i++] = *p->current++;
    }
    good_counts = i;
    while (i < RGBA_DIGITS) {
        buffer[i++] = 'f';
    }
    buffer[RGBA_DIGITS] = '\0';

    c->red = hextouc(buffer);
    c->green = hextouc(buffer + 2);
    c->blue = hextouc(buffer + 4);
    c->alpha = hextouc(buffer + 6);

    return good_counts;
}

size_t parse_colors(char *text, rgbalist_t *list) {
    parser_t parser;
    rgbacolor_t parsed;
    int check;
    size_t count;

    parser.body = text;
    parser.current = text;

    check = 0;
    count = 0;
    while (parser.current[0] != 0) {
        parse_spaces(&parser);
        switch (parser.current[0]) {
            case NAME_DELIMITER:
                parse_name(&parser, &parsed);
                check = 1;
                break;
            case HEX_DELIMITER:
                parse_hex(&parser, &parsed);
                rgbalist_insert(list, &parsed);
                if (check) check++;
                count++;
                break;
            default:
                parser.current++;
                check = 0;
        }
        // if (check == 2) {
        //     rgbalist_insert(list, &parsed);
        //     check = 0;
        //     count++;
        // }
    }

    return count;
}


int main(int argc, char **argv) {
    FILE *pf;
    long file_size;
    char *text;
    rgbalist_t *colors;
    size_t count;
    size_t i;

    if (argc != 2) {
        printf("Usage: %s <theme-name>\n", argv[0]);
        errno = EINVAL;
        perror("Could not start job");
        return 1;
    }

    pf = fopen(argv[1], "r");
    if (pf == NULL) {
        perror("Could not read theme");
        return 1;
    }

    /* copy file content into string */
    fseek(pf, 0, SEEK_END);
    file_size = ftell(pf);
    fseek(pf, 0, SEEK_SET);
    text = malloc(file_size + 1);
    if (text == NULL) {
        perror("Could not read theme");
        fclose(pf);
        return 1;
    }
    fread(text, file_size, 1, pf);
    text[file_size] = 0;
    fclose(pf);
    printf("text:\n%s", text);

    colors = rgbalist_create(DEFAULT_LIST_LEN);
    count = parse_colors(text, colors);

    printf("Counted %zu colors\n", count);
    for (i = 0; i < colors->count; i++) {
        printf("%zu Name: %s, \tred: %d, green: %d, blue: %d, alpha: %d\n", i, colors->element[i].name, colors->element[i].red, colors->element[i].green, colors->element[i].blue, colors->element[i].alpha);
    }






    free(text);
    printf("All done!\n");
    return 0;
}
