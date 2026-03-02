#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "rgba.h"
#include "token.h"

typedef struct _token {
        char     text[NAME_MAX_LEN + 1];
        uint8_t  type;
        uint16_t refcount;
} token_t;

extern token_t *tokCreate(void) {
        token_t *tok = malloc(sizeof (token_t));
        if (tok == NULL) return NULL;
        // memset(tok, 0, sizeof (token_t));
        tok->refcount = 1;
        return tok;
}

extern void tokRetain(token_t *t) {
        if (t == NULL) return;
        t->refcount++;
        return;
}

extern void tokRelease(token_t *t) {
        if (t == NULL) return;
        if (t->refcount == 0) return;
        if (--t->refcount == 0) {
                free(t);
        }
        return;
}

extern void tokSetType(token_t *t, uint8_t type) {
        if (t == 0) return;
        t->type = type;
        return;
}

extern void tokSetText(token_t *t, const char *stream) {
        if (t == NULL || stream == NULL) return;
        strncpy(t->text, stream, NAME_MAX_LEN);
        t->text[NAME_MAX_LEN] = 0;
        return;
}

extern uint8_t tokGetType(token_t *t) {
        if (t == 0) return TOK_ERR;
        return t->type;
}

extern const char *tokGetText(token_t *t) {
        if (t == NULL) {
                return NULL;
        }
        printf("toktxt: '%s'\n", t->text);
        return t->text;
}
