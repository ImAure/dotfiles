#ifndef PRIVATE_PARSER_H
#define PRIVATE_PARSER_H

#include "color.h"
#include "lexer.h"

typedef struct _parser {
        lexer_t *lx;
        token_t current;
} parser_t;

static inline token_t ps_peek(parser_t *ps);

#endif /* PRIVATE_PARSER_H */
