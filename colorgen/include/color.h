#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#define COLOR_NAME_MAX_LEN 256

typedef struct _color {
        enum {
                RGB,
                RGBA,
                ALIAS
        } type;
        char name[COLOR_NAME_MAX_LEN + 1];
        union {
                struct {
                        uint8_t r;
                        uint8_t g;
                        uint8_t b;
                } rgb;
                struct {
                        uint8_t r;
                        uint8_t g;
                        uint8_t b;
                        uint8_t a;
                } rgba;
                struct {
                        char name[COLOR_NAME_MAX_LEN + 1];
                } aliasof;
        } as;
} color_t;

extern void color_print(color_t color);

typedef struct _colorlist colorlist_t;

extern colorlist_t *colorlist_create(void);
extern void colorlist_destroy(colorlist_t *list);
extern void colorlist_insert_color(colorlist_t *list, color_t color);



#endif /* COLOR_H */
