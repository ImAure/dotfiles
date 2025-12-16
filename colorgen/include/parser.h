#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "rgba.h"
#include "token.h"
#include "lexer.h"

#define STR_KEY_NAME "name"
#define STR_KEY_VALUE "value"
#define STR_KEY_COLOR "color"

/* PARSER */

typedef struct _parser parser_t;

extern parser_t *psCreate(lexer_t *lx);
extern void      psRefrain(parser_t *ps);
extern void      psRelease(parser_t *ps);

extern void      psParse(char *json, rgbalist_t *colors, aliaslist_t *aliases);

#endif /* PARSER_H */
