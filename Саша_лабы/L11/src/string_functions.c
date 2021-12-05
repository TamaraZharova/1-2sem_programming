#include "../includes/string_functions.h"

#include <ctype.h>
#include <string.h>

#define FIELD_PUNCTUATION_LEN_START 2
// 2 = ':' + ' '
#define FIELD_PUNCTUATION_LEN_FINISH 2
// 2 = ';' + '\n'

int strIsblank(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isspace(str[i])) {
            return 0;
        }
    }
    return 1;
}

size_t numberLen(size_t num) {
    if (num == 0) {
        return 1;
    }
    size_t num_len = 0;
    while (num != 0) {
        num /= 10;
        num_len++;
    }
    return num_len;
}

char* getField(char* dest, const char* src) {
    char* src_needed = strchr(src, ':') + FIELD_PUNCTUATION_LEN_START;
    strncpy(dest, src_needed, strlen(src_needed) + 1);
    dest[strlen(dest) - FIELD_PUNCTUATION_LEN_FINISH] = '\0';
    return dest;
}
