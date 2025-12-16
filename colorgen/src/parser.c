#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "rgba.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"

enum _parserstatus {
        PS_ERR,
        PS_OK
};

typedef struct _parser {
        size_t       refcount;
        lexer_t     *lx;
        token_t     *tok;
        rgbacolor_t  color;
        rgbalist_t  *rgblist;
        aliaslist_t *aliaslist;
        uint8_t      status;
} parser_t;

extern parser_t *psCreate(lexer_t *lx) {
        if (lx == NULL) return NULL;
        parser_t *ps = malloc(sizeof (parser_t));
        if (ps == NULL) return NULL;
        ps->lx = lx;
        ps->tok = NULL;
        ps->status = PS_OK;
        return ps;
}

extern void psRefrain(parser_t *ps) {
        if (ps == NULL) return;
        ps->refcount++;
        return;
}

extern void psRelease(parser_t *ps) {
        if (ps == NULL) return;
        if (--ps->refcount == 0) free(ps);
        return;
}

static lexer_t *psGetLexer(parser_t *ps) {
        if (ps == NULL) return NULL;
        return ps->lx;
}

static token_t *psGetToken(parser_t *ps) {
        if (ps == NULL) return NULL;
        return ps->tok;
}

static uint8_t psGetStatus(parser_t *ps) {
        if (ps == NULL) return PS_ERR;
        return ps->status;
}

static void psSetLexer(parser_t *ps, lexer_t *lx) {
        if (ps == NULL) return;
        ps->lx = lx;
        return;
}

static void psSetToken(parser_t *ps, token_t *tok) {
        if (ps == NULL) return;
        ps->tok = tok;
        return;
}

static void psSetStatus(parser_t *ps, uint8_t status) {
        if (ps == NULL) return;
        ps->status = status;
        return;
}

static void psConsume(parser_t *ps, uint8_t type) {
        if (ps == NULL) return;
        if (psGetStatus(ps) == PS_ERR) return;
        if (tokGetType(psGetToken(ps)) == type) lxNextToken(psGetLexer(ps), psGetToken(ps));
}


static void psExpect(parser_t *ps, uint8_t type) {
        if (ps == NULL) return;
        if (psGetStatus(ps) == PS_ERR) return;
        if (tokGetType(psGetToken(ps)) == type) {
                lxNextToken(psGetLexer(ps), psGetToken(ps));
                return;
        }
        psSetStatus(ps, PS_ERR);
        return;
}

static void psParseKey(parser_t *ps, char *key) {
        if ((ps == NULL) || (key == NULL)) return;
        strncpy(tokGetText(psGetToken(ps)), key, NAME_MAX_LEN);
        key[NAME_MAX_LEN] = 0;
        return;
}


static void psParseColorObject(parser_t *ps) {
        /*
         * {
         *    "key": "val",
         *    "key": #val,
         *    ...
         * }
         */
        if (ps == NULL) return;
        char key[NAME_MAX_LEN + 1];
        rgbacolor_t color;
        color.isvalid = 0;
        psExpect(ps, TOK_LBRACE);
        if (tokGetStatus(psGetToken(ps)) != TOK_STRING) {
                psSetStatus(ps, PS_ERR);
                return;
        }
        psParseKey(ps, key);
        psExpect(ps, TOK_COLON);
        if (strncmp(key, STR_KEY_NAME, NAME_MAX_LEN) == 0) psParseName()


        /* ancora da fare */
}
static void psParsePalette(parser_t *ps) {
        if (ps == NULL) return;
        psExpect(ps, TOK_COLON);
        psExpect(ps, TOK_LBRACKET);
        if (psGetStatus(ps) == PS_ERR) return;
        while ((tokGetType(psGetToken(ps)) != TOK_RBRACKET) && (psGetStatus(ps) != PS_ERR)) {
                psParseColorObject(ps);
                psConsume(ps, TOK_COMMA);
        }
}











// static void psParsePalette(parser_t *ps) {
//         if (ps == NULL) return;
//         lxNextToken(psGetLexer(ps), psGetToken(ps));
//         if (tokGetType(psGetToken(ps)) == TOK_LBRACKET) lxNextToken(psGetLexer(ps), psGetToken(ps));
//         while ((tokGetType(psGetToken(ps)) != TOK_RBRACKET) && (psGetStatus(ps) != PS_ERR)) {
//                 switch (tokGetType(psGetToken(ps))) {
//                 case TOK_LBRACE:
//                         psParseObjsect(ps);
//                 case TOK_COMMA:
//                         lxNextToken(psGetLexer(ps), psGetToken(ps));
//                         break;
//                 default:
//                         psSetStatus(ps, PS_ERR);
//                 }
//         }
// }

static void psParseAliases(parser_t *ps) {
        /* simile */
}

static void psParseNext(parser_t *ps) {
        if (ps == NULL) return;
        lxNextToken(psGetLexer(ps), psGetToken(ps));
        uint8_t type = tokGetType(psGetToken(ps));
        char buffer[NAME_MAX_LEN + 1];
        strncpy(buffer, tokGetText(psGetToken(ps)), NAME_MAX_LEN);
        buffer[NAME_MAX_LEN] = 0;

        if (type == TOK_STRING) {
                if (strncmp(buffer, STR_PALETTE, NAME_MAX_LEN) == 0) {
                        psParsePalette(ps);
                } else if (strncmp(buffer, STR_ALIASES, NAME_MAX_LEN) == 0) {
                        psParseAliases(ps);
                }
        }
}

extern void psParse(char *json, rgbalist_t *colors, aliaslist_t *aliases) {
        lexer_t *lx = lxCreate(json);
        parser_t *ps = psCreate(lx);
        
        while ((tokGetType(psGetToken(ps)) != TOK_EOF) && (psGetStatus(ps) != PS_ERR)) {
                psParseNext(ps);
        }






        lxRelease(lx);
        psRelease(ps);
}




