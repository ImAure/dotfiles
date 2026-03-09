#ifndef PRIVATE_PARSER_H
#define PRIVATE_PARSER_H

#include "color.h"
#include "lexer.h"

#define STR_ALIASOF "aliasof"

typedef struct _parser {
        enum {
                PS_OK,
                PS_ERR,
                PS_DONE
        } status;
        lexer_t *lx;
        token_t current;
} parser_t;

static inline token_t ps_peek(parser_t *ps);
static void ps_advance(parser_t *ps);
static int ps_is_at_end(parser_t *ps);

#endif /* PRIVATE_PARSER_H */
