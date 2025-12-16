#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "token.h"

#define SYMBOL_QUOTES   '"'
#define SYMBOL_HASH     '#'
#define SYMBOL_LBRACE   '{'
#define SYMBOL_RBRACE   '}'
#define SYMBOL_LBRACKET '['
#define SYMBOL_RBRACKET ']'
#define SYMBOL_COLON    ':'
#define SYMBOL_COMMA    ','
#define SYMBOL_ERR      '?'
#define SYMBOL_EOF      "EOF"

#define STR_QUOTES   "\""
#define STR_HASH     "#"
#define STR_LBRACE   "{"
#define STR_RBRACE   "}"
#define STR_LBRACKET "["
#define STR_RBRACKET "]"
#define STR_COLON    ":"
#define STR_COMMA    ","
#define STR_ERR      "?"
#define STR_EOF      "EOF"
#define STR_PALETTE  "palette"
#define STR_ALIASES  "aliases"

typedef struct _lexer lexer_t;

extern lexer_t *lxCreate(char *json);
extern void     lxRetain(lexer_t *l);
extern void     lxRelease(lexer_t *l);
extern void     lxNextToken(lexer_t *l, token_t *tok);

#endif /* LEXER_H */
