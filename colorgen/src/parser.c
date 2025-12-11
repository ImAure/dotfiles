#include "parser.h"

typedef enum _toktype {
        TOK_STRING,         /* abc */
        TOK_COLON,          /* : */
        TOK_COMMA,          /* , */
        TOK_LBRACE,         /* { */
        TOK_RBRACE,         /* } */
        TOK_LBRACKET,       /* [ */
        TOK_RBRACKET,       /* ] */
        TOK_HASH,           /* # */
        TOK_HEX,            /* RRGGBBAA */
        TOK_EOF,
        TOK_ERR
} toktype_t;

typedef struct _token {
        toktype_t type;
        char      txt[NAME_MAX_LEN];
} token_t;

typedef struct _lexer {
        char *src;
        char *p;
} lexer_t;

lexer_t lxCreate(char *json) {
        lexer_t l;
        l.src = json;
        l.p   = json;
        return l;
}

int lxDestroy(lexer_t *l) {
        l->src = NULL;
        l->p   = NULL;
}


static inline char lxPeek(lexer_t *l) {
        return *l->p;
}

static inline char lxNext(lexer_t *l) {
        return *l->p++;
}

static void lxSkipSpaces(lexer_t *l) {
        while (isspace(lxPeek(l))) lxNext(l);
}

static token_t lxString(lexer_t *l) {
        token_t tok;
        tok.type = TOK_STRING;
        lxNext(l);
        size_t i = 0;
        while ((lxPeek(l) != 0) && (lxPeek(l) != SYMBOL_QUOTES) && (i < NAME_MAX_LEN)) {
                if (isalnum(lxPeek(l)) || lxPeek(l) == '-' || lxPeek(l) == '_') {
                        tok.txt[i++] = lxNext(l);
                } else {
                        lxNext(l);
                }
        }
        tok.txt[i] = 0;
        if (lxPeek(l) == SYMBOL_QUOTES) lxNext(l);
        return tok;
}

static token_t lxHex(lexer_t *l) {
        token_t tok;
        size_t i = 0;
        tok.type = TOK_HEX;
        while(isxdigit(lxPeek(l)) && (i < RGBA_LEN)) {
                tok.txt[i++] = lxNext(l);
        }
        tok.txt[i] = 0;
        if (i != RGBA_LEN) tok.type = TOK_ERR;
        return tok;
}

token_t lxNextToken(lexer_t *l) {
        lxSkipSpaces(l);
        char c = lxPeek(l);
        token_t tok;
        if (c == 0) {
                tok.type = TOK_EOF;
                strcpy(tok.txt, SYMBOL_EOF);
                return tok;
        }
        switch (c) {
                case SYMBOL_COLON:
                        tok.type = TOK_COLON;
                        *tok.txt = c;
                        lxNext(l);
                        return tok;
                case SYMBOL_HASH:
                        tok.type = TOK_HASH;
                        *tok.txt = c;
                        lxNext(l);
                        return tok;
                case SYMBOL_COMMA:
                        tok.type = TOK_COMMA;
                        *tok.txt = c;
                        lxNext(l);
                        return tok;
                case SYMBOL_LBRACE:
                        tok.type = TOK_LBRACE;
                        *tok.txt = c;
                        lxNext(l);
                        return tok;
                case SYMBOL_RBRACE:
                        tok.type = TOK_RBRACE;
                        *tok.txt = c;
                        lxNext(l);
                        return tok;
                case SYMBOL_LBRACKET:
                        tok.type = TOK_LBRACKET;
                        *tok.txt = c;
                        lxNext(l);
                        return tok;
                case SYMBOL_RBRACKET:
                        tok.type = TOK_RBRACKET;
                        *tok.txt = c;
                        lxNext(l);
                        return tok;
                case SYMBOL_QUOTES:
                        return lxString(l);

                default:
                        if (isxdigit(lxPeek(l))) return lxHex(l);
                        lxNext(l);
                        tok.type = TOK_ERR;
                        *tok.txt = SYMBOL_ERR;
                        return tok;
        }
}
