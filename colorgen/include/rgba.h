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

typedef struct _rgbacolor  rgbacolor_t;
typedef struct _rgbalist   rgbalist_t;
typedef struct _aliascolor aliascolor_t;
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

