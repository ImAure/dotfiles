#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

/*========== CONSTANTS ==========*/
#define STRLEN 1024
#define NAME_MAX_LEN 256
#define LIST_BASE_LEN 32
#define RGBA_LEN 8
#define FILL_FACTOR 0.7

/*========== DELIMITERS ==========*/
#define SYMBOL_QUOTES '\"'
#define SYMBOL_HASH '#'
#define SYMBOL_LBRACE '{'
#define SYMBOL_RBRACE '}'
#define SYMBOL_LBRACKET '['
#define SYMBOL_RBRACKET ']'
#define SYMBOL_COLON ':'
#define SYMBOL_COMMA ','
#define SYMBOL_ERR '?'
#define SYMBOL_EOF "EOF"

#define KEY_PALETTE "palette"
#define KEY_COLOR "color"
#define KEY_ALIASES "aliases"


/*============================================================
 *===== DATA STRUCTURES ======================================
 *==========================================================*/

typedef struct _rgbacolor {
    char name[NAME_MAX_LEN];
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} rgbacolor_t;

typedef struct _rgbalist {
    uint32_t ref;
    size_t len;
    size_t count;
    rgbacolor_t *element;
} rgbalist_t;

typedef struct _jsonobj {
    enum {
        JSON_ALIAS,
        JSON_COLOR
    } type;
    union {
        char alias_name[NAME_MAX_LEN];
        rgbacolor_t color;
    };
} jsonobj_t;

typedef enum _toktype {
    TOK_STRING, /* abc */
    TOK_COLON, /* : */
    TOK_COMMA, /* , */
    TOK_LBRACE, /* { */
    TOK_RBRACE, /* } */
    TOK_LBRACKET, /* [ */
    TOK_RBRACKET, /* ] */
    TOK_HASH,   /* # */
    TOK_HEX, /* RRGGBBAA */
    TOK_EOF,
    TOK_ERR
} toktype_t;

typedef struct _token {
    toktype_t type;
    char txt[NAME_MAX_LEN];
} token_t;

/*============================================================
 *===== DYNAMICAL ARRAY ======================================
 *==========================================================*/

rgbalist_t rgbalCreate(size_t len) {
    if (len == 0) len = LIST_BASE_LEN;
    rgbalist_t list;
    list.len = len;
    list.count = 0;
    list.element = malloc(len * sizeof(rgbacolor_t));
    if (list.element == NULL) memset(&list, 0, sizeof(list));
    return list;
}

rgbalist_t rgbalDestroy(rgbalist_t *list) {
    rgbalist_t empty;
    memset(&empty, 0, sizeof(rgbalist_t));
    if (list == NULL) return empty;
    if (list->element) free(list->element);
    memset(list, 0, sizeof(rgbalist_t));
    return *list;
}

static inline size_t rgbalGetCount(rgbalist_t *list) {
    return list->count;
}

static inline size_t rgbalGetLen(rgbalist_t *list) {
    return list->len;
}

int rgbalInsert(rgbalist_t *const list, rgbacolor_t *new) {
    if (list == NULL || new == NULL) return 1;
    size_t len = rgbalGetLen(list);
    size_t count = rgbalGetCount(list);
    if (len == 0) return 1;
    if (((double)count) / ((double)len) < FILL_FACTOR) {
        list->element = realloc(list->element, 2 * len * sizeof(rgbacolor_t));
        if (list->element == NULL) return 1;
        list->len = len * 2;
    }
    list->element[count] = *new;
    list->count++;
    return 0;
}

/*============================================================
 *===== LEXER ================================================
 *==========================================================*/

typedef struct _lexer {
    char *src;
    char *p;
} lexer_t;

lexer_t lxCreate(char *json) {
    lexer_t l;
    l.src = json;
    l.p = json;
    return l;
}

static inline char lxPeek(lexer_t *l) {
    return *l->p;
}

static inline char lxNext(lexer_t *l) {
    return *l->p++;
}

void lxSkipSpaces(lexer_t *l) {
    while (isspace(lxPeek(l))) lxNext(l);
}

token_t lxString(lexer_t *l) {
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

token_t lxHex(lexer_t *l) {
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

/*============================================================
 *===== PARSER ===============================================
 *==========================================================*/

typedef struct _parser {
    lexer_t *lx;
    token_t tok;
    enum {PS_ERR, PS_OK} status;
} parser_t;

parser_t psCreate(lexer_t *l) {
    parser_t p;
    p.lx = l;
    p.status = PS_OK;
    p.tok = lxNextToken(l);
    return p;
}

static inline token_t psPeek(parser_t *p) {
    return p->tok;
}

static inline token_t psNext(parser_t *p) {
    return p->tok = lxNextToken(p->lx);
}

int psExpect(parser_t *p, toktype_t t) {
    if (p->tok.type != t) {
        p->status = PS_ERR;
        return 1;
    }
    return 0;
}

// root
// |---palette
// |   |---list
// |       |---color
// |           |---pairlist
// |               |---pair
// |                   |---name
// |                   |---hex
// |---aliases       
//     |---list
//         |---alias
//             |---pairlist
//                 |---pair
//                     |---name
//                     |---alias


int psConsume(parser_t *p, toktype_t t) {
    if (psExpect(p, t)) return 1;
    psNext(p);
    return 0;
}

int psParseValue(parser_t *p) {

    switch (p->tok.type) {
        case: TOK_STRING;
        case: TOK_HEX;
    }
    return 0;
}

int psParsePair(parser_t *p) {

    return 0;
}

int psParsePairList(parser_t *p) {

    return 0;
}

rgbacolor_t psParseColorObj(parser_t *p) {
    rgbacolor_t parsed;
    psConsume(p, TOK_LBRACE);
    psParsePairList(p);
    psExpect(p, TOK_RBRACE);
    
    /*
     * da FARE!!!
     * forza napoli
     */

    return parsed;
}

rgbalist_t psParsePalette(parser_t *p) {
    rgbalist_t list = rgbalCreate(LIST_BASE_LEN);
    if (p == NULL) {
        return rgbalDestroy(&list);
    }
    if (rgbalGetLen(&list) == 0) return rgbalDestroy(&list);
    if (psConsume(p, TOK_COLON)) return rgbalDestroy(&list);
    if (psConsume(p, TOK_LBRACKET)) return rgbalDestroy(&list);

    rgbacolor_t parsed;

    while(!psExpect(p, TOK_RBRACKET)) {
        parsed = psParseColorObj(p);
        rgbalInsert(&list, &parsed);
        psNext(p);
    }
    return list;
}

int psParseRoot(parser_t *p, rgbalist_t *list, aliaslist_t *aliases) {

    
}











// int psParseObject() {
//
// }
//
// int psParseValue(parser_t *p) {
//     switch (p->tok.type) {
//         case TOK_STRING:
//             psNext(p);
//             return 0;
//         case TOK_HEX:
//             psNext(p);
//             return 0;
//         case TOK_LBRACE:
//             return psParseObject(p);
//         default:
//             p->status = PS_ERR;
//             return 1;
//     }
// }
//
// int psParsePair(parser_t *p) {
//     if (psExpect(p, TOK_STRING)) return 1;
//
//     char *key = strdup(p->tok.txt);
//     psNext(p);
//
//     if (psConsume(p, TOK_COLON)) {
//         free(key);
//         return 1;
//     }
//
//     if (strcmp(key, KEY_PALETTE)) {
//
//     }
// } 
//
// it psParsePairList(parser_t *p) {
//
// }
//
// int psParseObject(parser_t *p) {
//     if (psConsume(p, TOK_LBRACE)) return 1;
//
//     if (p->tok.type == TOK_RBRACE) {
//         psNext(p);
//         return 0;
//     }
//
//     if (psParsePairList(p)) return 1;
//     if (psConsume(p, TOK_RBRACE)) return 1;
//
//     return 0;
// }
//
// int psParseRoot(parser_t *p) {
//     return parseObject(p);
// }
//
//
// int parseValue(parser_t *p) {
//     switch (p->tok.type) {
//         case TOK_STRING:
//             psNext(p);
//             return 1;
//         case TOK_HEX:
//             psNext(p);
//             return 1;
//     }
// }














/*============================================================
 *===== PARSING ==============================================
 *==========================================================*/
// int parser_is_valid(parser_t *p) {
//     return (p != NULL) && (p->body != NULL) && (p->current != NULL);
// }
//
// int parse_spaces(parser_t *p) {
//     if (!parser_is_valid(p)) return 1;
//
//     while (isspace(*p->current)) {
//         // parser->type = PARSER_TYPE_SPACE;
//         p->current++;
//     }
// }
//
// int parse_string(parser_t *p, char *buffer) {
//     if (!parser_is_valid(p)) { return 1; }
//     if (*parser->current != SYMBOL_DELIMITER_NAME) { return 1; }
//
//
//     size_t i;
//     for (i = 0; parser->current[i])
// }
//

/*============================================================
 *===== MAIN =================================================
 *==========================================================*/
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments.\nUsage: %s path/to/file", argv[0]);
        return 1;
    }

    FILE *fp;
    size_t file_size;
    char *text;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Could not read file");
        return 1;
    }

    /* get file size */
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    /* allocate memory for text and load file */
    text = malloc(file_size + 1);
    if (text == NULL) {
        perror("Could not load file");
        fclose(fp);
        return 1;
    }
    fread(text, file_size, 1, fp);
    text[file_size] = 0;
    fclose(fp);

    /* parse text */
    lexer_t l = lxCreate(text);
    token_t t;

    while (t.type != TOK_EOF) {
        t = lxNextToken(&l);
        printf("Token: %d,\t\"%s\"\n", t.type, t.txt);
    }






    free(text);
    return 0;
}




