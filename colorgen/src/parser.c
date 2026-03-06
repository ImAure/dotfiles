#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "color.h"
#include "parser.h"
#include "private-parser.h"

#define PARSER_DEBUG

extern parser_t *ps_create(char *json) {
        parser_t *ps = malloc(sizeof *ps);
        if (ps == NULL) return NULL;
        ps->lx = lx_create(json);
        if (ps->lx == NULL) {
                free(ps);
                return NULL;
        }
        ps->state = PS_START;
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

static inline int ps_is_at_end(parser_t *ps) {
        return (ps_peek(ps).type == TOK_EOF);
}

static inline int ps_match(parser_t *ps, tokentype_t type) {
        return (ps->current.type == type);
}

static void ps_print_status(parser_t *ps) {
        printf("PARSER STATUS: ");
        switch (ps->state) {
                case PS_START: printf("START"); break;
                case PS_COLOR: printf("COLOR"); break;
                // case PS_PAIR: printf("PAIR"); break;
                case PS_ERR: printf("ERR"); break;
                case PS_DONE: printf("DONE"); break;
                default: printf("bo..."); break;
        }
        printf("\n");
}

static void ps_advance(parser_t *ps) {
        ps->current = lx_next_token(ps->lx);
        switch (ps->current.type) {
                case TOK_ERR:     ps->state = PS_ERR;  break;
                case TOK_EOF:     ps->state = PS_DONE; break;
                case TOK_COMMENT: ps_advance(ps);      break;
                default: break;
        }
        token_print(ps_peek(ps));
        ps_print_status(ps);
}

static int ps_expect(parser_t *ps, tokentype_t type) {
        if (ps_match(ps, type)) {
                ps_advance(ps);
                return 1;
        }
        return 0;
}

static void ps_consume(parser_t *ps, tokentype_t type) {
        if (ps_match(ps, type)) ps_advance(ps);
}

// color_t ps_parse_color(parser_t *ps) {
//         color_t c;
//
//         strncpy(color.name, ps_parse_name(ps), COLOR_NAME_MAX_LEN);
//         color.name[COLORN_NAME_MAX_LEN] = 0;
//
//
//
//
//
//
//         return c;
// }

extern colorlist_t *ps_parse_colorlist(char *json) {
        if (json == NULL) return NULL;
        colorlist_t *list = colorlist_create();
        if (list == NULL) return NULL;
        parser_t *ps = ps_create(json);
        if (ps == NULL) return NULL;
        while (ps->state != PS_ERR && ps->state != PS_DONE) {
                ps_advance(ps);
                switch (ps->state) {
                case PS_ERR:
                        colorlist_destroy(list);
                        return NULL;
                case PS_DONE:
                        ps_destroy(ps);
                        return list;
                default:
                        continue;
                }
        }
        ps_destroy(ps);
        colorlist_destroy(list);
        return NULL;
}
