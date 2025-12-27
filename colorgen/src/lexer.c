#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "rgba.h"
#include "token.h"
#include "lexer.h"

/* LEXER */

typedef struct _lexer {
        size_t  refcount;
        char   *src;
        char   *p;
} lexer_t;

extern lexer_t *lxCreate(char *json) {
        lexer_t *lx = malloc(sizeof (lexer_t));
        if (lx == NULL) return NULL;
        lx->refcount = 1;
        lx->src = json;
        lx->p   = json;
        return lx;
}

extern void lxRetain(lexer_t *lx) {
        if (lx == NULL) return;
        lx->refcount++;
        return;
}

extern void lxRelease(lexer_t *lx) {
        if (lx == NULL) return;

        if (--lx->refcount == 0) {
                memset(lx, 0, sizeof (lexer_t));
                free(lx);
        }
        return;
}

static inline char lxPeek(lexer_t *lx) {
        return *lx->p;
}

static inline char lxNext(lexer_t *lx) {
        return *lx->p++;
}

static void lxSkipSpaces(lexer_t *lx) {
        while (isspace(lxPeek(lx))) lxNext(lx);
}

static void lxString(lexer_t *lx, token_t *tok) {
        if (lx == NULL || tok == NULL) return;
        char buffer[NAME_MAX_LEN + 1];
        size_t i = 0;
        lxNext(lx);
        while ((lxPeek(lx) != 0) && (lxPeek(lx) != SYMBOL_QUOTES) && (i < NAME_MAX_LEN)) {
                if (isalnum(lxPeek(lx)) || lxPeek(lx) == '-' || lxPeek(lx) == '_') {
                        buffer[i++] = lxNext(lx);
                } else {
                        lxNext(lx);
                }
        }
        buffer[i] = 0;
        if (lxPeek(lx) != SYMBOL_QUOTES) {
                tokSetType(tok, TOK_ERR);
                return;
        }
        tokSetType(tok, TOK_STRING);
        tokSetText(tok, buffer);
        lxNext(lx);
        return;
}

static void lxHex(lexer_t *lx, token_t *tok) {
        if ((lx == NULL) || (tok == NULL)) return;
        size_t i = 0;
        char buffer[RGBA_LEN + 1];
        while(isxdigit(lxPeek(lx)) && (i < RGBA_LEN)) {
                buffer[i++] = lxNext(lx);
        }
        buffer[i] = 0;
        if (i != RGBA_LEN) {
                tokSetType(tok, TOK_ERR);
                return;
        }
        tokSetType(tok, TOK_HEX);
        tokSetText(tok, buffer);
        return;
}

extern void lxNextToken(lexer_t *lx, token_t *tok) {
        if ((lx == NULL) || (tok == NULL)) return;
        char c;
        lxSkipSpaces(lx);
        c = lxPeek(lx);

        switch (c) {
        case 0:
                printf("lxNextToken: EOF\n");
                tokSetType(tok, TOK_EOF);
                tokSetText(tok, SYMBOL_EOF);
                return;
        case SYMBOL_COLON:
                printf("lxNextToken: COLON\n");
                tokSetType(tok, TOK_COLON);
                tokSetText(tok, STR_COLON);
                lxNext(lx);
                return;
        case SYMBOL_COMMA:
                printf("lxNextToken: COMMA\n");
                tokSetType(tok, TOK_COMMA);
                tokSetText(tok, STR_COMMA);
                lxNext(lx);
                return;
        case SYMBOL_LBRACE:
                printf("lxNextToken: LBRACE\n");
                tokSetType(tok, TOK_LBRACE);
                tokSetText(tok, STR_LBRACE);
                lxNext(lx);
                return;
        case SYMBOL_RBRACE:
                printf("lxNextToken: RBRACE\n");
                tokSetType(tok, TOK_RBRACE);
                tokSetText(tok, STR_RBRACE);
                lxNext(lx);
                return;
        case SYMBOL_LBRACKET:
                printf("lxNextToken: LBRACKET\n");
                tokSetType(tok, TOK_LBRACKET);
                tokSetText(tok, STR_LBRACKET);
                lxNext(lx);
                return;
        case SYMBOL_RBRACKET:
                printf("lxNextToken: RBRACKET\n");
                tokSetType(tok, TOK_RBRACKET);
                tokSetText(tok, STR_RBRACKET);
                lxNext(lx);
                return;
        case SYMBOL_QUOTES:
                printf("lxNextToken: STRING\n");
                lxString(lx, tok);
                return;
        default:
                printf("lxNextToken: ERR\n");
                tokSetType(tok, TOK_ERR);
                tokSetText(tok, STR_ERR);
                lxNext(lx);
                return;
        }
}



// extern token_t lxNextToken(lexer_t *lx) {
//         lxSkipSpaces(lx);
//         char c = lxPeek(lx);
//         token_t tok; /* riscrivere con puntatore / oggetto */
//         if (c == 0) {
//                 tok.type = TOK_EOF;
//                 strcpy(tok.text, SYMBOL_EOF);
//                 return tok;
//         }
//         switch (c) {
//                 case SYMBOL_COLON:
//                         tok.type = TOK_COLON;
//                         *tok.text = c;
//                         lxNext(lx);
//                         return tok;
//                 case SYMBOL_HASH:
//                         tok.type = TOK_HASH;
//                         *tok.text = c;
//                         lxNext(lx);
//                         return tok;
//                 case SYMBOL_COMMA:
//                         tok.type = TOK_COMMA;
//                         *tok.text = c;
//                         lxNext(lx);
//                         return tok;
//                 case SYMBOL_LBRACE:
//                         tok.type = TOK_LBRACE;
//                         *tok.text = c;
//                         lxNext(lx);
//                         return tok;
//                 case SYMBOL_RBRACE:
//                         tok.type = TOK_RBRACE;
//                         *tok.text = c;
//                         lxNext(lx);
//                         return tok;
//                 case SYMBOL_LBRACKET:
//                         tok.type = TOK_LBRACKET;
//                         *tok.text = c;
//                         lxNext(lx);
//                         return tok;
//                 case SYMBOL_RBRACKET:
//                         tok.type = TOK_RBRACKET;
//                         *tok.text = c;
//                         lxNext(lx);
//                         return tok;
//                 case SYMBOL_QUOTES:
//                         return lxString(lx);
//
//                 default:
//                         if (isxdigit(lxPeek(lx))) return lxHex(lx);
//                         lxNext(lx);
//                         tok.type = TOK_ERR;
//                         *tok.text = SYMBOL_ERR;
//                         return tok;
//         }
// }

// static token_t lxString(lexer_t *lx) {
//         token_t tok;
//         tok.type = TOK_STRING;
//         lxNext(lx);
//         size_t i = 0;
//         while ((lxPeek(lx) != 0) && (lxPeek(lx) != SYMBOL_QUOTES) && (i < NAME_MAX_LEN)) {
//                 if (isalnum(lxPeek(lx)) || lxPeek(lx) == '-' || lxPeek(lx) == '_') {
//                         tok.text[i++] = lxNext(lx);
//                 } else {
//                         lxNext(lx);
//                 }
//         }
//         tok.text[i] = 0;
//         if (lxPeek(lx) == SYMBOL_QUOTES) lxNext(lx);
//         return tok;
// }

// static token_t lxHex(lexer_t *lx) {
//         token_t tok;
//         size_t i = 0;
//         tok.type = TOK_HEX;
//         while(isxdigit(lxPeek(lx)) && (i < RGBA_LEN)) {
//                 tok.text[i++] = lxNext(lx);
//         }
//         tok.text[i] = 0;
//         if (i != RGBA_LEN) tok.type = TOK_ERR;
//         return tok;
// }
