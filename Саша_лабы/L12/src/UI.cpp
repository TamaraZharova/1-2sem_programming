#include "../includes/UI.h"
#include "../includes/structs.h"
#include "../includes/file_funcs.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define SUCCESS 0;
#define FILE_OPENING_ERROR -1;
#define MEMORY_ALLOCATING_ERROR -2;

int addMediaUI(const char *file_path) {
    FILE *file = fopen(file_path, "ab");
    if (!file) {
        return FILE_OPENING_ERROR;
    }

    Book *book = (Book *) malloc(sizeof(Book));
    if (!book) {
        fclose(file);
        return MEMORY_ALLOCATING_ERROR;
    }

    puts("Input a book:");
    readBook(book);
    puts("");

    size_t arr_num = countElements(file, sizeof(Book));
    fWriteElement<Book>(file, book, arr_num);

    free(book);
    fclose(file);
    return SUCCESS;
}

int printMediaUI(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        return FILE_OPENING_ERROR;
    }

    Book *book = (Book *) malloc(sizeof(Book));
    if (!book) {
        fclose(file);
        return MEMORY_ALLOCATING_ERROR;
    }

    puts("Existing books:");
    size_t arr_num = countElements(file, sizeof(Book));
    for (size_t i = 0; i < arr_num; i++) {
        fReadElement<Book>(book, file, i);
        printBook(book);
        puts("");
    }

    free(book);
    fclose(file);
    return SUCCESS;
}

static void fSortBooks(FILE *file, int (*cmp)(Book *, Book *)) {
    size_t arr_num = countElements(file, sizeof(Book));
    Book *book_a = (Book *) malloc(sizeof(Book));
    if (!book_a) {
        return;
    }
    Book *book_b = (Book *) malloc(sizeof(Book));
    if (!book_b) {
        free(book_a);
        return;
    }
    for (size_t i = 0; i < arr_num; i++) {
        for (size_t j = arr_num - 1; j >= i + 1; j--) {
            fReadElement<Book>(book_a, file, j);
            fReadElement<Book>(book_b, file, j - 1);
            if (cmp(book_a, book_b) < 0) {
                fSwapElements<Book>(file, j, j - 1);
            }
        }
    }
}

int sortMediaUI(const char *file_path) {
    FILE *file = fopen(file_path, "rb+");
    if (!file) {
        return FILE_OPENING_ERROR;
    }

    puts("What field do you want to sort by:");
    puts("1. Name;");
    puts("2. Rank;");
    size_t choice = 0;
    scanf("%zu", &choice);
    puts("");

    switch (choice) {
        case 1:
            fSortBooks(file, &cmpBookName);
            break;
        case 2:
            fSortBooks(file, &cmpBookRank);
            break;
        default:
            puts("Wrong choice");
            break;
    }
    fclose(file);
    return SUCCESS;
}

int deleteMediaUI(const char *file_path) {
    FILE *file = fopen(file_path, "rb+");
    if (!file) {
        return FILE_OPENING_ERROR;
    }

    char *author = (char *) malloc(FIELD_LEN * sizeof(char));
    if (!author) {
        fclose(file);
        return MEMORY_ALLOCATING_ERROR;
    }

    puts("Author to delete by:");
    scanf("%s", author);
    puts("");

    Book *book = (Book *) malloc(sizeof(Book));
    if (!book) {
        fclose(file);
        free(author);
        return MEMORY_ALLOCATING_ERROR;
    }

    size_t arr_num = countElements(file, sizeof(Book));
    for (size_t i = 0; i < arr_num; i++) {
        fReadElement<Book>(book, file, i);
        if (strstr(book->Author, author)) {
            fDeleteElement<Book>(file, i);
            arr_num--;
            i--;
        }
    }


    free(author);
    free(book);
    fclose(file);
    return SUCCESS;
}
