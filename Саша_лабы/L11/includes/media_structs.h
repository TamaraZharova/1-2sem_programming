#ifndef LW_11_MEDIA_STRUCTS_H
#define LW_11_MEDIA_STRUCTS_H

#include <stdlib.h>
#include <stdio.h>

#define FIELD_LEN 255
#define FIELD_NUM 4
#define STR_LEN 300

typedef struct {
    char Name[FIELD_LEN];
    char Author[FIELD_LEN];
    int PageCount;
    int Rank;
} Book;

typedef struct {
    Book *arr;
    size_t arr_num;
} Books_arr;

// Working with Books_arr structs --------------------------------------------

Books_arr *allocBooksArr(void);

void freeBooksArr(Books_arr *books);

void writeBooksArr(FILE *stream, Books_arr *books);

void addBook(Books_arr *media_file, char **fields);

void sortBooksArr(Books_arr *books);

void deleteBook(Books_arr *books, const char* author);

#endif //LW_11_MEDIA_STRUCTS_H
