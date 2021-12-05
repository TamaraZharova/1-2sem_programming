#include "file_functions.h"
#include "string_functions.h"
#include "media_structs.h"

#include <stdio.h>
#include <string.h>

// Task 1 ---------------------------------------------------------------------

static size_t charInFile(FILE *file, char chr) {
    size_t counter = 0;
    while (!feof(file)) {
        if (fgetc(file) == chr) {
            counter++;
        }
    }
    rewind(file);
    return counter;
}

static size_t maxStrLen(FILE *file) {
    size_t max_len = 0;
    size_t cur_len = 0;
    while (!feof(file)) {
        char chr = (char) fgetc(file);
        cur_len++;
        if (chr == '\n') {
            if (cur_len > max_len) {
                max_len = cur_len;
            }
            cur_len = 0;
        }

    }
    if (cur_len > max_len) {
        max_len = cur_len;
    }
    rewind(file);
    return max_len;
}

String_array *createFromFile(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        return NULL;
    }

    size_t num = charInFile(file, '\n') + 1;
    size_t max_len = maxStrLen(file);
    if (!max_len) {
        fclose(file);
        return NULL;
    }

    String_array *string_array = allocStrArr(num, max_len + 1);  // (+ 1) because of terminated-null
    if (!string_array) {
        fclose(file);
        return NULL;
    }

    for (size_t i = 0; i < num; i++) {
        fgets(string_array->str_arr[i], (int) max_len + 1, file);
        if (strchr(string_array->str_arr[i], '\n')) {
            string_array->str_arr[i][strlen(string_array->str_arr[i]) - 1] = '\0';
        }
    }

    fclose(file);
    return string_array;
}

void writeToFile(const char *file_path, const String_array *string_array) {
    FILE *file = fopen(file_path, "w");
    if (!file) {
        return;
    }

    for (size_t i = 0; i < string_array->num; i++) {
        fputs(string_array->str_arr[i], file);
        fputc('\n', file);
    }

    fclose(file);
}

// Task 2 ---------------------------------------------------------------------

// adds books to Books_arr from stream
static int fAddBooks(Books_arr *books, FILE *stream) {
    size_t file_pos = ftell(stream);

    char *string = malloc(STR_LEN * sizeof(char));
    if (!string) {
        return -1;
    }

    String_array *fields = allocStrArr(FIELD_NUM, STR_LEN);
    if (!fields) {
        return -1;
    }

    int field_num = 0;
    while (!feof(stream)) {
        fgets(string, STR_LEN, stream);
        if (field_num) {
            getField(fields->str_arr[field_num], string);
            field_num++;
            if (field_num == FIELD_NUM) {
                field_num = 0;
                addBook(books, fields->str_arr);
            }
        } else {
            if (strstr(string, "Name:")) {
                getField(fields->str_arr[field_num], string);
                field_num++;
            }
        }
    }

    free(string);
    freeStrArr(fields);
    fseek(stream, file_pos, SEEK_SET);
    return 0;
}

Books_arr *fCreateBooksArr(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        return NULL;
    }

    Books_arr *books = allocBooksArr();
    if (!books) {
        fclose(file);
        return NULL;
    }

    fAddBooks(books, file);

    fclose(file);
    return books;
}

int fWriteBooksArr(const char *file_path, Books_arr *books) {
    FILE *file = fopen(file_path, "w");
    if (!file) {
        return -1;
    }
    writeBooksArr(file, books);
    fclose(file);
    return 0;
}
