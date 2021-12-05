#ifndef LW_12_FILE_FUNCS_H
#define LW_12_FILE_FUNCS_H

#include "../includes/structs.h"

#include <unistd.h>
#include <cstdio>
#include <cstdlib>

size_t countElements(FILE *file, size_t size);

template<typename T>
void fWriteElement(FILE *file, T *elem, size_t index) {
    long start_pos = ftell(file);

    fseek(file, index * sizeof(T), SEEK_SET);
    fwrite(elem, sizeof(T), 1, file);

    fseek(file, start_pos, SEEK_SET);
}

template<typename T>
void fReadElement(T *elem, FILE *file, size_t index) {
    long start_pos = ftell(file);

    fseek(file, index * sizeof(T), SEEK_SET);
    fread(elem, sizeof(T), 1, file);

    fseek(file, start_pos, SEEK_SET);
}

template<typename T>
void fSwapElements(FILE *file, size_t index_a, size_t index_b) {
    T *a = (T *) malloc(sizeof(Book));
    if (!a) {
        return;
    }
    T *b = (T *) malloc(sizeof(Book));
    if (!b) {
        free(a);
        return;
    }
    fReadElement<T>(a, file, index_a);
    fReadElement<T>(b, file, index_b);
    fWriteElement<T>(file, b, index_a);
    fWriteElement<T>(file, a, index_b);

    free(a);
    free(b);
}

template<typename T>
void fDeleteElement(FILE *file, size_t index) {
    long start_pos = ftell(file);

    fseek(file, index * sizeof(T), SEEK_SET);
    size_t arr_num = countElements(file, sizeof(T));
    for (size_t i = index; i < arr_num - 1; i++) {
        fSwapElements<T>(file, i, i + 1);
    }

    size_t new_size = (arr_num - 1) * sizeof(T);
    ftruncate(fileno(file), new_size);

    fseek(file, start_pos, SEEK_SET);
}

#endif //LW_12_FILE_FUNCS_H
