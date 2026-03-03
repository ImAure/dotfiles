#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "private-color.h"

extern void color_print(color_t color) {
        printf("COLOR as ");
        switch (color.type) {
        case RGB:
                printf("RGB\tname: '%s'\t value: r: %d, g: %d, b: %d\n", color.name, color.as.rgb.r, color.as.rgb.g, color.as.rgb.b);
                break;
        case RGBA:
                printf("RGBA\tname: '%s'\t value: r: %d, g: %d, b: %d, a: %d\n", color.name, color.as.rgba.r, color.as.rgba.g, color.as.rgba.b, color.as.rgba.a);
                break;
        case ALIAS:
                printf("ALIAS\tname: '%s'\t alias of '%s'\n", color.name, color.as.aliasof.name);
                break;
        }
}

extern colorlist_t *colorlist_create(void) {
        colorlist_t *list = malloc(sizeof *list);
        if (list == NULL) return NULL;
        list->colors = malloc(sizeof (color_t) * COLORLIST_BASE_LEN);
        if (list->colors == NULL) return NULL;
        list->capacity = COLORLIST_BASE_LEN;
        list->count = 0;
        return list;
}

extern void colorlist_destroy(colorlist_t *list) {
        if (list) {
                if (list->colors) free(list->colors);
                free(list);
        }
}

extern void colorlist_insert_color(colorlist_t *list, color_t color) {
        if (list == NULL) return;
        if (list->colors == NULL) return;

        if ((float)list->count / (float)list->capacity < COLORLIST_FILL_FACTOR) {
                list->colors = realloc(list->colors, 2 * sizeof (color_t) * list->capacity);
                if (list->colors == NULL) { return; }
                list->capacity *= 2;
        }
        list->colors[list->count++] = color;
}

extern void colorlist_print(colorlist_t *list) {
        if (list == NULL) {
                perror("Cannot print list: null pointer");
                return;
        }
        if (list->colors == NULL) {
                perror("Cannot print list: null pointer to elements");
                return;
        }
        if (list->count == 0) {
                printf("List is empty\n");
        }
        size_t i;
        for (i = 0; i < list->count; i++) {
                color_print(list->colors[i]);
        }
        return;
}
