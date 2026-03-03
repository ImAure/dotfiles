#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "lexer.h"
#include "private-lexer.h"

static void token_print(token_t tok) {
        printf("TOKEN at %zu:%zu,\tlen: %zu,\ttxt: '%.*s'\n", tok.line, tok.column, tok.len, (int)tok.len, tok.start);
}

extern lexer_t *lx_create(char *stream) {
        lexer_t *lx = malloc(sizeof *lx);
        if (lx == NULL) return NULL;
        lx->src = stream;
        lx->p = stream;
        lx->line = 1;
        lx->column = 1;
        return lx;
}

extern void lx_destroy(lexer_t *lx) {
        if (lx) free(lx);
}

static inline char lx_peek(lexer_t *lx) {
        return *lx->p;
}

static void lx_advance(lexer_t *lx) {
        lx->p++;
        if (lx_peek(lx) == SYM_NULLTERM) return;
        if (lx_peek(lx) == '\n') {
                lx->column = 1;
                lx->line++;
        } else {
                lx->column++;
        }
}

static void lx_skip_spaces(lexer_t *lx) {
        while (isspace(lx_peek(lx))) lx_advance(lx);
}

static token_t lx_tokenize_symbol(lexer_t *lx, tokentype_t type, size_t len) {
        token_t tok;
        tok.type = type;
        tok.start = lx->p;
        tok.len = len;
        tok.line = lx->line;
        tok.column = lx->column;
        return tok;
}

static token_t lx_tokenize_string(lexer_t *lx) {
        token_t tok;
        lx_advance(lx);
        tok = lx_tokenize_symbol(lx, TOK_STRING, 0);
        while (lx_peek(lx) != SYM_NULLTERM && lx_peek(lx) != SYM_QUOTES) {
                lx_advance(lx);
                tok.len++;
        }
        if (lx_peek(lx) == SYM_NULLTERM) return lx_tokenize_symbol(lx, TOK_ERR, 1);
        return tok;
}

extern token_t lx_next_token(lexer_t *lx) {
        token_t tok;
        lx_skip_spaces(lx);
        switch (lx_peek(lx)) {
        case SYM_LBRACE:
                tok = lx_tokenize_symbol(lx, TOK_LBRACE, 1);
                lx_advance(lx);
                break;
        case SYM_RBRACE: 
                tok = lx_tokenize_symbol(lx, TOK_RBRACE, 1);
                lx_advance(lx);
                break;
        case SYM_LBRACKET:
                tok = lx_tokenize_symbol(lx, TOK_LBRACKET, 1);
                lx_advance(lx);
                break;
        case SYM_RBRACKET:
                tok = lx_tokenize_symbol(lx, TOK_LBRACKET, 1);
                lx_advance(lx);
                break;
        case SYM_COLON:
                tok = lx_tokenize_symbol(lx, TOK_COLON, 1);
                lx_advance(lx);
                break;
        case SYM_COMMA:
                tok = lx_tokenize_symbol(lx, TOK_COMMA, 1);
                lx_advance(lx);
                break;
        case SYM_QUOTES:
                tok = lx_tokenize_string(lx);
                lx_advance(lx);
                break;
        case SYM_NULLTERM:
                tok = lx_tokenize_symbol(lx, TOK_EOF, 1);
                break;
        default:
                tok = lx_tokenize_symbol(lx, TOK_ERR, 1);
                lx_advance(lx);
                break;
        }
        token_print(tok);
        return tok;
}
