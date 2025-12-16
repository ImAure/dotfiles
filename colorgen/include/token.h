#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

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

typedef struct _token token_t;

extern token_t *tokCreate(void);
extern void     tokRetain(token_t *t);
extern void     tokRelease(token_t *t);

extern void tokSetType(token_t *t, uint8_t type);
extern void tokSetText(token_t *t, const char *stream);

extern uint8_t     tokGetType(token_t *t);
extern const char *tokGetText(token_t *t);

#endif /* TOKEN_H */
