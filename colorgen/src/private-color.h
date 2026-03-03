
#ifndef PRIVATE_COLOR_H
#define PRIVATE_COLOR_H

#define COLORLIST_FILL_FACTOR 0.7
#define COLORLIST_BASE_LEN 32

typedef struct _colorlist {
        size_t capacity;
        size_t count;
        color_t *colors;
} colorlist_t;


#endif /* PRIVATE_COLOR_H */
