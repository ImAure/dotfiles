#include "rgba.h"
#include "lexer.h"
#include "parser.h"


typedef struct _token {
        char    text[NAME_MAX_LEN + 1];
        uint8_t type;
        uint16_t refcount;
} token_t;

int main(void) {
        printf("ciao!\n");
        lexer_t *l = lxCreate(NULL);
        printf("ciao, l'adi mensione: %zu\n", sizeof (token_t));

        printf("ilcoloreeeeee %x\n", 255);
        char prova[400];
        int ciao;
        scanf("%x", &ciao);
        printf("%d, %x", ciao, ciao);
        unsigned int blue = ciao & 255;
        unsigned int green = (ciao & (65536 - 255)) >> 8;
        unsigned int red = (ciao & (16777216 - 65536)) >> 16;
        printf("red: %u\ngreen: %u\nblue: %u\n", red, green, blue);





        return 0;

}

