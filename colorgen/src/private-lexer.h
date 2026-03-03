
#ifndef PRIVATE_LEXER_H
#define PRIVATE_LEXER_H

#define SYM_LBRACE   '{'
#define SYM_RBRACE   '}'
#define SYM_LBRACKET '['
#define SYM_RBRACKET ']'
#define SYM_COLON    ':'
#define SYM_COMMA    ','
#define SYM_QUOTES   '"'
#define SYM_NULLTERM  0

typedef struct _lexer {
        const char *src;
        char *p;
        size_t line;
        size_t column;
} lexer_t;

static inline char lx_peek(lexer_t *lx);
static void lx_advance(lexer_t *lx);
static void lx_skip_spaces(lexer_t *lx);
static token_t lx_tokenize_string(lexer_t *lx);
static token_t lx_tokenize_symbol(lexer_t *lx, tokentype_t type, size_t len);
static void token_print(token_t tok);
#endif /* PRIVATE_LEXER_H */

