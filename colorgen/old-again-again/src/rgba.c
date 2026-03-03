#include "rgba.h"

extern uint8_t rgbaStrToByte(char *stream) {
        if (stream == NULL) return 0;
        if (!(isxdigit(stream[0]) && isxdigit(stream[1]))) return 0;

        uint8_t value = 0;
        if (stream[0] >= '0' && stream[0] <= '9') value += (stream[0] - '0') * 16;
        else if (stream[0] >= 'a' && stream[0] <= 'f') value += (stream[0] - 'a' + 10) * 16;
        else if (stream[0] >= 'A' && stream[0] <= 'F') value += (stream[0] - 'A' + 10) * 16;

        if (stream[1] >= '0' && stream[1] <= '9') value += (stream[1] - '0');
        else if (stream[1] >= 'a' && stream[1] <= 'f') value += (stream[1] - 'a' + 10);
        else if (stream[1] >= 'A' && stream[1] <= 'F') value += (stream[1] - 'A' + 10);

        return value;
}

typedef struct _rgbalist {
        size_t refcount;
        size_t capacity;
        size_t count;
        rgbacolor_t *item;
} rgbalist_t;

typedef struct _aliaslist {
        size_t refcount;
        size_t capacity;
        size_t count;
        aliascolor_t *item;
} aliaslist_t;

extern rgbalist_t *rgbalCreate(size_t len) {
        rgbalist_t *list = malloc(sizeof (rgbalist_t));
        if (list == NULL) return NULL;

        len = (len > LIST_BASE_LEN ? len : LIST_BASE_LEN);
        list->item = malloc(len * sizeof (rgbacolor_t));
        if (list->item == NULL) {
                free(list);
                return NULL;
        }

        list->refcount = 1;
        list->capacity = len;
        list->count = 0;

        return list;
}

extern void rgbalRefrain(rgbalist_t *list) {
        if (list == NULL) return;
        list->refcount++;
        return;
}

extern void rgbalRelease(rgbalist_t *list) {
        if (list == NULL) return;

        if (--list->refcount == 0) {
                if (list->item) free(list->item);
                free(list);
        }

        return;
}

extern void rgbalPush(rgbalist_t *list, rgbacolor_t *new) {
        if (list == NULL || new == NULL) return;
        if (list->capacity == 0) return;
                
        size_t len = list->capacity;
        size_t count = list->count;

        if (((double)count) / ((double)len) < FILL_FACTOR) {
                list->item = realloc(list->item, 2 * len * sizeof (rgbacolor_t));
                if (list->item == NULL) return;

                list->capacity = len * 2;
        }

        list->item[count] = *new;
        list->count++;

        return;
}










extern aliaslist_t *aliaslCreate(size_t len) {
        aliaslist_t *list = malloc(sizeof (aliaslist_t));
        if (list == NULL) return NULL;

        len = (len > LIST_BASE_LEN ? len : LIST_BASE_LEN);
        list->item = malloc(len * sizeof (aliascolor_t));
        if (list->item == NULL) {
                free(list);
                return NULL;
        }

        list->refcount = 1;
        list->capacity = len;
        list->count = 0;

        return list;
}

extern void aliaslRefrain(aliaslist_t *list) {
        if (list == NULL) return;
        list->refcount++;
        return;
}

extern void aliaslRelease(aliaslist_t *list) {
        if (list == NULL) return;

        if (--list->refcount == 0) {
                if (list->item) free(list->item);
                free(list);
        }

        return;
}

extern void aliaslPush(aliaslist_t *list, aliascolor_t *new) {
        if (list == NULL || new == NULL) return;
        if (list->capacity == 0) return;
                
        size_t len = list->capacity;
        size_t count = list->count;

        if (((double)count) / ((double)len) < FILL_FACTOR) {
                list->item = realloc(list->item, 2 * len * sizeof (aliascolor_t));
                if (list->item == NULL) return;

                list->capacity = len * 2;
        }

        list->item[count] = *new;
        list->count++;

        return;
}
