#include "media_structs.h"

#include <string.h>

static int cmpBookRank(Book *a, Book *b) {
    if (a->Rank > b->Rank) {
        return 1;
    } else if (a->Rank < b->Rank) {
        return -1;
    } else {
        return 0;
    }
}

static void swapBooks(Book *a, Book *b) {
    Book tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sortBooks(Books_arr *books, int (*cmp)(Book *, Book *)) {
    for (size_t i = 0; i < books->arr_num; i++) {
        for (size_t j = books->arr_num - 1; j >= i + 1; j--) {
            if (cmp(&books->arr[j], &books->arr[j - 1]) < 0) {
                swapBooks(&books->arr[j], &books->arr[j - 1]);
            }
        }
    }
}

// Working with Books_arr structs --------------------------------------------

Books_arr *allocBooksArr(void) {
    Books_arr *books = calloc(1, sizeof(Books_arr));
    if (!books) {
        return NULL;
    }

    return books;
}

void freeBooksArr(Books_arr *books) {
    free(books->arr);
    free(books);
}

void writeBooksArr(FILE *stream, Books_arr *books) {
    for (size_t i = 0; i < books->arr_num; i++) {
        fprintf(stream, "Name: %s;\n", books->arr[i].Name);
        fprintf(stream, "Author: %s;\n", books->arr[i].Author);
        fprintf(stream, "PageCount: %d;\n", books->arr[i].PageCount);
        fprintf(stream, "Rank: %d;\n\n", books->arr[i].Rank);
    }
}

static int allocBook(Books_arr *books) {
    size_t new_size = (books->arr_num + 1) * sizeof(Book);
    Book *tmp_books = realloc(books->arr, new_size);
    // TODO: realloc sometimes doesn't works (when i try to input to existing items)
    if (!tmp_books) {
        return -1;
    }
    if (books->arr != tmp_books) {
        books->arr = tmp_books;
    }
    books->arr_num++;
    return 0;
}

// adds book with fields to Books_arr
void addBook(Books_arr *books, char **fields) {
    if (allocBook(books)) {
        return;
    }
    strncpy(books->arr[books->arr_num - 1].Name, fields[0], strlen(fields[0]) + 1);
    strncpy(books->arr[books->arr_num - 1].Author, fields[1], strlen(fields[1]) + 1);
    books->arr[books->arr_num - 1].PageCount = atoi(fields[2]);
    books->arr[books->arr_num - 1].Rank = atoi(fields[3]);
}

void sortBooksArr(Books_arr *books) {
    sortBooks(books, &cmpBookRank);
}

void deleteBook(Books_arr *books, const char *author) {
    for (size_t i = 0; i < books->arr_num; i++) {
        if (strstr(books->arr[i].Author, author)) {
            for (size_t j = i; j < books->arr_num - 1; j++) {
                swapBooks(&books->arr[j], &books->arr[j + 1]);
            }
            books->arr_num--;
            i--;
        }
    }
}
