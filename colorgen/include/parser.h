#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "color.h"

typedef struct _parser parser_t;

extern parser_t *ps_create(char *json);
extern void ps_destroy(parser_t *ps);
extern colorlist_t *ps_parse_colorlist(char *json);






#endif /* PARSER_H */ 
