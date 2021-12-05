#include "file_functions.h"
#include "media_structs.h"
#include "string_arrays.h"
#include "UI.h"

#include <stdlib.h>

int addMediaUI(const char *file_path) {
    Books_arr *books = fCreateBooksArr(file_path);

    String_array *fields = allocStrArr(FIELD_NUM, STR_LEN);
    if (!fields) {
        return -1;
    }

    // TODO: scanf reads only till space found
    printf("Name: ");
    scanf("%s", fields->str_arr[0]);
    printf("Author: ");
    scanf("%s", fields->str_arr[1]);
    printf("PageCount: ");
    scanf("%s", fields->str_arr[2]);
    printf("Rank: ");
    scanf("%s", fields->str_arr[3]);

    addBook(books, fields->str_arr);

    fWriteBooksArr(file_path, books);

    freeBooksArr(books);
    freeStrArr(fields);
    return 0;
}

int printMediaUI(const char *file_path) {
    Books_arr *books = fCreateBooksArr(file_path);
    puts("Existing books:");
    writeBooksArr(stdout, books);

    freeBooksArr(books);
    return 0;
}

int sortMediaUI(const char *file_path) {
    Books_arr *books = fCreateBooksArr(file_path);
    sortBooksArr(books);
    fWriteBooksArr(file_path, books);
    freeBooksArr(books);
    return 0;
}

int deleteMediaUI(const char *file_path) {
    Books_arr *books = fCreateBooksArr(file_path);

    char *author = malloc(STR_LEN * sizeof(char));
    puts("Author to delete by:");
    scanf("%s", author);
    deleteBook(books, author);
    free(author);

    fWriteBooksArr(file_path, books);
    freeBooksArr(books);
    return 0;
}
