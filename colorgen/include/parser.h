#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "rgba.h"


/* LEXER */

#define SYMBOL_QUOTES   '\"'
#define SYMBOL_HASH     '#'
#define SYMBOL_LBRACE   '{'
#define SYMBOL_RBRACE   '}'
#define SYMBOL_LBRACKET '['
#define SYMBOL_RBRACKET ']'
#define SYMBOL_COLON    ':'
#define SYMBOL_COMMA    ','
#define SYMBOL_ERR      '?'
#define SYMBOL_EOF      "EOF"

typedef struct _token token_t;
typedef struct _lexer lexer_t;

extern lexer_t lxCreate(char *json);
extern int     lxDestroy(lexer_t *l);
extern token_t lxNextToken(lexer_t *l);

/* PARSER */

typedef struct _parser parser_t;

extern parser_t psCreate(lexer_t *l);
extern int      psParse(parser_t *p, rgbalist_t *colors, aliaslist_t *aliases);











#endif /* PARSER_H */
