#include "../includes/string_arrays.h"
#include "../includes/string_functions.h"

#include <stdio.h>
#include <string.h>

#define ENUM_PUNCTUATION_LEN 2

static void swap(char **a, char **b) {
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void delStrArrEl(String_array *string_array, size_t index) {
    for (size_t i = index; i < string_array->num - 1; i++) {
        swap(&string_array->str_arr[i], &string_array->str_arr[i + 1]);
    }
    free(string_array->str_arr[string_array->num - 1]);
    string_array->num--;
}

String_array *allocStrArr(size_t num, size_t max_len) {
    char **str_arr = malloc(num * sizeof(char *));
    if (!str_arr) {
        return NULL;
    }

    String_array *string_array = malloc(sizeof(String_array));
    if (!string_array) {
        free(str_arr);
        return NULL;
    }
    string_array->num = num;
    string_array->str_arr = str_arr;

    for (size_t i = 0; i < num; i++) {
        string_array->str_arr[i] = malloc(max_len * sizeof(char));
        if (!string_array->str_arr[i]) {
            string_array->num = i;
            freeStrArr(string_array);
            return NULL;
        }
    }
    return string_array;
}

void freeStrArr(String_array *string_array) {
    for (size_t i = 0; i < string_array->num; i++) {
        free(string_array->str_arr[i]);
    }
    free(string_array->str_arr);
    free(string_array);
}

void deleteBlankStr(String_array *string_array) {
    for (size_t i = 0; i < string_array->num; i++) {
        if (strIsblank(string_array->str_arr[i])) {
            delStrArrEl(string_array, i);
            i--;
        }
    }
}

int numberStr(String_array *string_array) {
    for (size_t i = 0; i < string_array->num; i++) {
        size_t new_size = strlen(string_array->str_arr[i]) + numberLen(i + 1) + ENUM_PUNCTUATION_LEN + 1;
        char *tmp_str = malloc(new_size * sizeof(char));
        if (!tmp_str) {
            return -1;
        }
        sprintf(tmp_str, "%zu. %s", i + 1, string_array->str_arr[i]);
        free(string_array->str_arr[i]);
        string_array->str_arr[i] = tmp_str;
    }
    return 0;
}
