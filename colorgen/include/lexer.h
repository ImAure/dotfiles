#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

/* TOKEN STUFF */
typedef enum _tokentype {
        TOK_LBRACE,
        TOK_RBRACE,
        TOK_LBRACKET,
        TOK_RBRACKET,
        TOK_COLON,
        TOK_COMMA,
        TOK_STRING,
        TOK_EOF,
        TOK_ERR
} tokentype_t;

typedef struct _token {
        tokentype_t type;
        char *start;
        size_t len;
        size_t line;
        size_t column;
} token_t;

/* LEXER STUFF */


typedef struct _lexer lexer_t;

extern lexer_t *lx_create(char *stream);
extern void lx_destroy(lexer_t *lx);
extern token_t lx_next_token(lexer_t *lx);

#endif /* LEXER_H */

