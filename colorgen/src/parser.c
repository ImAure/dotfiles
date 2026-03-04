#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "color.h"
#include "parser.h"
#include "private-parser.h"

extern parser_t *ps_create(char *json) {
        parser_t *ps = malloc(sizeof *ps);
        if (ps == NULL) return NULL;
        ps->lx = lx_create(json);
        if (ps->lx == NULL) {
                free(ps);
                return NULL;
        }
        ps->current = lx_next_token(ps->lx);
        return ps;
}

extern void ps_destroy(parser_t *ps) {
        if (ps == NULL) return;
        if (ps->lx) lx_destroy(ps->lx);
        free(ps);
}

static inline token_t ps_peek(parser_t *ps) {
        return ps->current;
}

static void ps_advance(parser_t *ps) {
        token_t tok = ps_peek(ps);
        if (tok.type == TOK_ERR) {
                printf("ce stato un rore... mi sa ke nn pss andare avant1..\na... vuoi sapere dov e.. ok... %zu:%zu\n", tok.line, tok.column);
        }
        ps->current = lx_next_token(ps->lx);
        return;
}

static int ps_is_at_end(parser_t *ps) {
        return (ps_peek(ps).type == TOK_EOF);
}

static int ps_match(parser_t *ps, tokentype_t type) {
        return (ps->current.type == type);
}

extern colorlist_t *ps_parse_colors(char *json) {
        if (json == NULL) return NULL;
        colorlist_t *list = colorlist_create();
        if (list == NULL) return NULL;
        parser_t *ps = ps_create(json);
        if (ps == NULL) return NULL;
        while (!ps_is_at_end(ps)) {
                ps_advance(ps);
        }










        ps_destroy(ps);
        return list;
}
