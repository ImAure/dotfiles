#include <stdint.h>
#include <stdlib.h>

#include "color.h"
#include "private-color.h"









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
