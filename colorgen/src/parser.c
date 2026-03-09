#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "color.h"
#include "parser.h"
#include "private-parser.h"

#define CASE_PRINT(A) case (A): printf("%s", #A); break
#define MAX(A, B) ((A) > (B)) ? (A) : (B)
#define MIN(A, B) ((A) < (B)) ? (A) : (B)

#define PARSER_DEBUG

extern parser_t *ps_create(char *json) {
        parser_t *ps = malloc(sizeof *ps);
        if (ps == NULL) return NULL;
        ps->lx = lx_create(json);
        if (ps->lx == NULL) {
                free(ps);
                return NULL;
        }
        ps->status = PS_OK;
        // ps->current = lx_next_token(ps->lx);
        ps->current = (token_t){ 0 };
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
        switch (ps->status) {
                CASE_PRINT(PS_OK);
                CASE_PRINT(PS_ERR);
                CASE_PRINT(PS_DONE);
        }
        printf("\n");
}

static void ps_advance(parser_t *ps) {
        ps->current = lx_next_token(ps->lx);
        switch (ps->current.type) {
                case TOK_ERR:     ps->status = PS_ERR;  break;
                case TOK_EOF:     ps->status = PS_DONE; break;
                case TOK_COMMENT: ps_advance(ps);       break;
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
        ps->status = PS_ERR;
        return 0;
}

static inline void ps_consume(parser_t *ps, tokentype_t type) {
        if (ps_match(ps, type)) ps_advance(ps);
}

static uint8_t hextobyte(const char *s) {
        if ((*s == 0) || (*(s + 1) == 0)) return 0;
        char buf[3] = {s[0], s[1], 0};
        return strtol(buf, NULL, 16);
}

static void ps_parse_value(parser_t *ps, color_t* color) {
        if (ps_match(ps, TOK_STRING)) {
                switch (ps->current.len - 1) {
                case 6: /* |#|RRGGBB| */
                        color->type = RGB;
                        color->as.rgb.r = hextobyte(ps->current.start+1);
                        color->as.rgb.g = hextobyte(ps->current.start+1+2);
                        color->as.rgb.b = hextobyte(ps->current.start+1+4);
                        break;
                case 8: /* |#|RRGGBBAA| */
                        color->type = RGBA;
                        color->as.rgba.r = hextobyte(ps->current.start+1);
                        color->as.rgba.g = hextobyte(ps->current.start+1+2);
                        color->as.rgba.b = hextobyte(ps->current.start+1+4);
                        color->as.rgba.a = hextobyte(ps->current.start+1+6);
                        break;
                default:
                        ps->status = PS_ERR;
                        return;
                }
                ps_advance(ps);
        }
        if (ps_match(ps, TOK_LBRACE)) {
                printf("L'HO TROVATA LA PARENTESI\n");
                color->type = ALIAS;
                ps_advance(ps);
                if (!ps_match(ps, TOK_STRING)) {
                        ps->status = PS_ERR;
                        return;
                }
                if (strncmp(ps->current.start, STR_ALIASOF, ps->current.len) == 0) {
                        ps_advance(ps);
                        if (!ps_expect(ps, TOK_COLON)) return;
                        memcpy(color->as.aliasof.name, ps->current.start, MIN(ps->current.len, COLOR_NAME_MAX_LEN));
                        ps_advance(ps);
                        ps_expect(ps, TOK_RBRACE);
                }
        }

}

static void ps_parse_member(parser_t *ps, colorlist_t *list) {
        while (ps_match(ps, TOK_COMMA)) {
                ps_consume(ps, TOK_COMMA);
        }
        if (!ps_match(ps, TOK_STRING)) goto PS_PARSE_MEMBER_ERR;
        color_t color = (color_t){ 0 };

        memcpy(color.name, ps->current.start, MIN(ps->current.len, COLOR_NAME_MAX_LEN));
        color.name[COLOR_NAME_MAX_LEN] = 0;
        ps_advance(ps);

        if (!ps_expect(ps, TOK_COLON)) goto PS_PARSE_MEMBER_ERR;
        if (!(ps_match(ps, TOK_STRING) || ps_match(ps, TOK_LBRACE))) goto PS_PARSE_MEMBER_ERR;
        ps_parse_value(ps, &color);
        colorlist_insert_color(list, color);
        return;

        PS_PARSE_MEMBER_ERR:
        printf("===== PARSE_MEMBER_ERR =====\n");
        ps->status = PS_ERR;
}

static void ps_parse_members(parser_t *ps, colorlist_t *list) {
        do {
                ps_parse_member(ps, list);
                if (ps_match(ps, TOK_RBRACE)) break;
        } while ((ps->status != PS_ERR) && ps_expect(ps, TOK_COMMA));
}


extern colorlist_t *parse_palette(char *json) {
        if (json == NULL) return NULL;
        parser_t *ps = ps_create(json);
        colorlist_t *list = colorlist_create();
        if (ps == NULL) goto PARSE_PALETTE_ERR;
        if (list == NULL) goto PARSE_PALETTE_ERR; 

        ps_advance(ps);
        if (!ps_expect(ps, TOK_LBRACE)) goto PARSE_PALETTE_ERR;
        if (!ps_match(ps, TOK_RBRACE)) {
                ps_parse_members(ps, list);
                if (ps_match(ps, TOK_RBRACE)) printf("io direi che ho finito\n");
                ps_print_status(ps);
                if (ps->status == PS_ERR) goto PARSE_PALETTE_ERR;
        }

        ps_destroy(ps);
        return list;

        PARSE_PALETTE_ERR:
        printf("===== PARSE_PALETTE_ERR =====\n");
        if (ps) ps_destroy(ps);
        if (list) colorlist_destroy(list);
        return NULL;
}

// static char *ps_parse_key(parser_t *ps) {
//         printf("sta per succ\n");
//         char *buffer = malloc(sizeof (char) * (ps->current.len + 1));
//         if (buffer == NULL) return NULL;
//         strncpy(buffer, ps->current.start, MAX(ps->current.len, COLOR_NAME_MAX_LEN));
//         buffer[COLOR_NAME_MAX_LEN] = 0;
//         return buffer;
// }
//
// static color_t ps_parse_value(parser_t *ps);
//
// color_t ps_parse_member(parser_t *ps) {
//         if (ps->status != PS_OK) return (color_t){ 0 };
//         color_t color = (color_t){ 0 };
//         // strncpy(color.name, ps_parse_name(ps), COLOR_NAME_MAX_LEN);
//         color.name[COLOR_NAME_MAX_LEN] = 0;
//         char *buffer = NULL;
//         switch (ps->current.type) {
//                 case TOK_STRING:
//                         printf("qualcuno mas\n");
//                         buffer = ps_parse_key(ps);
//                         ps_advance(ps);
//                         break;
//                 default:
//                         ps->status = PS_ERR;
//                         #ifdef PARSER_DEBUG
//                          printf("È RORE! in ps_parse_colorlist\n");
//                         #endif
//         }
//         // color = ps_parse_value(ps);
//         strncpy(color.name, buffer, COLOR_NAME_MAX_LEN + 1);
//         free(buffer);
//         ps_expect(ps, TOK_COLON);
//         ps_expect(ps, TOK_STRING);
//         ps_expect(ps, TOK_COMMA);
//
//         return color;
// }
//
//
// extern colorlist_t *ps_parse_colorlist(char *json) {
//         if (json == NULL) return NULL;
//         parser_t *ps = ps_create(json);
//         if (ps == NULL) return NULL;
//         ps_advance(ps);
//         if (!ps_match(ps, TOK_LBRACE)) {
//                 printf("Could not procede\n");
//                 ps_destroy(ps);
//                 return NULL;
//         }
//         colorlist_t *list = colorlist_create();
//         if (list == NULL) return NULL;
//         int i = 0;
//         token_print(ps_peek(ps));
//         ps_print_status(ps);
//         while (ps->status == PS_OK) {
//                 ps_advance(ps);
//                 token_print(ps_peek(ps));
//                 ps_print_status(ps);
//         }
//         ps_destroy(ps);
//         return list;
// }
