#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "private-color.h"


#define COLOR_DEBUG

extern void color_print(color_t color) {
        printf("Color: %s\n", color.name);
        switch (color.type) {
        case RGB:
                printf("type: RGB\n\tr: %d\n\tg: %d\n\tb: %d\n", color.as.rgb.r, color.as.rgb.g, color.as.rgb.b);
                // printf("RGB\n\tname: '%s'\n\tvalue:\n\tr: %d,\n\tg: %d,\n\tb: %d\n", color.name, color.as.rgb.r, color.as.rgb.g, color.as.rgb.b);
                break;
        case RGBA:
                printf("type: RGBA\n\tr: %d\n\tg: %d\n\tb: %d\n\ta: %d\n", color.as.rgba.r, color.as.rgba.g, color.as.rgba.b, color.as.rgba.a);
                break;
        case ALIAS:
                printf("type: ALIAS\n\tof: %s\n", color.as.aliasof.name);
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

        if (((float)list->count / (float)list->capacity) > COLORLIST_FILL_FACTOR) {
                list->colors = realloc(list->colors, 2 * list->capacity * sizeof (color_t));
                if (list->colors == NULL) {
                        return;
                }
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

static color_t *colorlist_find(colorlist_t *list, const char *name, size_t depth) {
        if (depth >= list->count) {
#ifdef COLOR_DEBUG
                printf("Cyclic aliases!\n");
#endif /* COLOR_DEBUG */
                return NULL;
        }
        for (size_t i = 0; i < list->count; i++) {
                if (strcmp(list->colors[i].name, name) == 0) {
                        if (list->colors[i].type == ALIAS) return colorlist_find(list, list->colors[i].as.aliasof.name, depth + 1);
                        else return &list->colors[i];
                }
        }
        return NULL;
}

extern void colorlist_resolve_aliases(colorlist_t *list) {
        for (size_t i = 0; i < list->count; i++) {
                if (list->colors[i].type == ALIAS) {
                        color_t *target = colorlist_find(list, list->colors[i].as.aliasof.name, 0);
                        if (target == NULL) {
#ifdef COLOR_DEBUG
                                printf("Could not resolve alisas: %s -> %s\n", list->colors[i].name, list->colors[i].as.aliasof.name);
#endif /* COLOR_DEBUG */
                                continue;
                        }
                        list->colors[i].type = target->type;
                        list->colors[i].as = target->as;
                }
        }
}
