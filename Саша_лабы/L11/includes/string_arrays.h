#ifndef LW_11_STRING_ARRAYS_H
#define LW_11_STRING_ARRAYS_H

#include <stdlib.h>

typedef struct {
    char **str_arr;
    size_t num;
} String_array;

String_array *allocStrArr(size_t num, size_t max_len);

void freeStrArr(String_array *string_array);

void deleteBlankStr(String_array *string_array);

int numberStr(String_array *string_array);

#endif //LW_11_STRING_ARRAYS_H
