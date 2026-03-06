#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

#include "lexer.h"
#include "private-lexer.h"

extern void token_print(token_t tok) {
        printf("TOKEN at %zu:%zu,\tl: %zu,\ttxt: '%.*s'\n", tok.line, tok.column, tok.len, (int)tok.len, tok.start);
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
        if (lx_peek(lx) == '\n') {
                lx->line++;
                lx->column = 1;
        } else {
                lx->column++;
        }
        if (lx_peek(lx) != SYM_NULLTERM) lx->p++;
}

static token_t lx_make_token(lexer_t *lx, tokentype_t type) {
        token_t tok;
        tok.type = type;
        tok.start = lx->p;
        tok.len = 0;
        tok.line = lx->line;
        tok.column = lx->column;
        return tok;
}

static inline int isnull(char c) {
        return (c == 0);
}

static inline int issymbol(char c) {
        switch(c) {
                case SYM_LBRACE:
                case SYM_RBRACE:
                case SYM_LBRACKET:
                case SYM_RBRACKET:
                case SYM_COLON:
                case SYM_COMMA:
                case SYM_HYPHEN:
                        return 1;
                default:
                        return 0;
        }
}

static inline int isquotes(char c) {
        return (c == SYM_QUOTES);
}

static inline int isslash(char c) {
        return (c == SYM_SLASH);
}

static inline token_t lx_tokenize_eof(lexer_t *lx) {
        return lx_make_token(lx, TOK_EOF);
}

static inline token_t lx_tokenize_err(lexer_t *lx) {
        token_t tok = lx_make_token(lx, TOK_ERR);
        tok.len = 1;
        return tok;
}

static inline token_t lx_tokenize_symbol(lexer_t *lx) {
        char current = lx_peek(lx);
        tokentype_t type;
        token_t tok;
        switch (current) {
                case SYM_LBRACE:   type = TOK_LBRACE;   break;
                case SYM_RBRACE:   type = TOK_RBRACE;   break; 
                case SYM_LBRACKET: type = TOK_LBRACKET; break;
                case SYM_RBRACKET: type = TOK_RBRACKET; break;
                case SYM_COLON:    type = TOK_COLON;    break;
                case SYM_COMMA:    type = TOK_COMMA;    break;
                case SYM_HYPHEN:   type = TOK_HYPHEN;   break;
                default:           type = TOK_ERR;    break;
        }
        tok = lx_make_token(lx, type);
        lx_advance(lx);
        tok.len = 1;
        return tok;
}

static void lx_skip_spaces(lexer_t *lx) {
        while (isspace((uint8_t)lx_peek(lx))) lx_advance(lx);
}

static token_t lx_tokenize_comment(lexer_t *lx) {
        token_t tok = lx_make_token(lx, TOK_COMMENT);
        lx_advance(lx);
        tok.len++;
        if (lx_peek(lx) != SYM_SLASH) return lx_tokenize_err(lx);
        while (!isnull(lx_peek(lx)) && (lx_peek(lx) != SYM_NEWLINE)) {
                lx_advance(lx);
                tok.len++;
        }
        return tok;
}

static token_t lx_tokenize_int(lexer_t *lx) {
        token_t tok = lx_make_token(lx, TOK_INT);
        while (isdigit(lx_peek(lx))) {
                lx_advance(lx);
                tok.len++;
        }
        return tok;
}

static token_t lx_tokenize_ident(lexer_t * lx) {
        token_t tok = lx_make_token(lx, TOK_ERR);
        while (islower(lx_peek(lx))) {
                lx_advance(lx);
                tok.len++;
        }
        if (tok.len == 4 && strncmp(tok.start, STR_TRUE, 4) == 0) tok.type = TOK_TRUE;
        else if (tok.len == 5 && strncmp(tok.start, STR_FALSE, 5) == 0) tok.type = TOK_FALSE;
        else tok.type = TOK_ERR;
        return tok;
}

static token_t lx_tokenize_string(lexer_t *lx) {
        token_t tok;
        lx_advance(lx);
        tok = lx_make_token(lx, TOK_STRING);
        while (!isnull(lx_peek(lx)) && !isquotes(lx_peek(lx))) {
                lx_advance(lx);
                tok.len++;
        }
        if (isnull(lx_peek(lx))) return lx_tokenize_err(lx);
        lx_advance(lx);
        return tok;
}


extern token_t lx_next_token(lexer_t *lx) {
        lx_skip_spaces(lx);
        char current = lx_peek(lx);
        if (isnull((char)current))   return lx_tokenize_eof(lx);
        if (isdigit((char)current))  return lx_tokenize_int(lx);
        if (islower((char)current))  return lx_tokenize_ident(lx);
        if (issymbol((char)current)) return lx_tokenize_symbol(lx);
        if (isquotes((char)current)) return lx_tokenize_string(lx);
        if (isslash((char)current))  return lx_tokenize_comment(lx);
        return lx_tokenize_err(lx);
}
