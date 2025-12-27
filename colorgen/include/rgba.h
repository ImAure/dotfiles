#ifndef RGBA_H
#define RGBA_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define NAME_MAX_LEN  256
#define LIST_BASE_LEN 32
#define RGBA_LEN      8
#define FILL_FACTOR   0.7

typedef struct _rgbacolor {
        /* +-+------//-+-+-+-+-+
         * |F| NAME    |R|G|B|A|
         * +-+------//-+-+-+-+-+ */
        uint8_t isvn:1;
        uint8_t isvr:1;
        uint8_t isvg:1;
        uint8_t isvb:1;
        uint8_t isalpha:1;
        uint8_t isva:1;
        char    name[NAME_MAX_LEN + 1];
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
} rgbacolor_t;

typedef struct _aliascolor {
        /* +-+------//-+-------//-+
         * |F| NAME    | ALIAS    |
         * +-+------//-+-------//-+ */
        uint8_t isvalid:4;
        uint8_t isalpha:4;
        char    name[NAME_MAX_LEN + 1];
        char    alias[NAME_MAX_LEN + 1];
        uint8_t a;
} aliascolor_t;

typedef struct _rgbalist   rgbalist_t;
typedef struct _aliaslist  aliaslist_t;

extern rgbalist_t *rgbalCreate(size_t len);
extern void        rgbalRefrain(rgbalist_t *list);
extern void        rgbalRelease(rgbalist_t *list);
extern void        rgbalPush(rgbalist_t *list, rgbacolor_t *new);

extern aliaslist_t *aliaslCreate(size_t len);
extern void         aliaslRefrain(aliaslist_t *list);
extern void         aliaslRelease(aliaslist_t *list);
extern void         aliaslPush(aliaslist_t *list, aliascolor_t *new);

#endif /* RGBA_H */

