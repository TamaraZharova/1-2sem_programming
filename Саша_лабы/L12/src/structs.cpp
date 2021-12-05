#include "../includes/structs.h"

#include <cstdio>
#include <cstring>

void readBook(Book *book) {
    printf("Name: ");
    scanf("%s", book->Name);
    printf("Author: ");
    scanf("%s", book->Author);
    printf("PageCount: ");
    scanf("%d", &book->PageCount);
    printf("Rank: ");
    scanf("%d", &book->Rank);
}

void printBook(Book *book) {
    printf("Name: %s;\n", book->Name);
    printf("Author: %s;\n", book->Author);
    printf("PageCount: %d;\n", book->PageCount);
    printf("Rank: %d;\n", book->Rank);
}

int cmpBookName(Book *a, Book *b) {
    return strcmp(a->Name, b->Name);
}

int cmpBookRank(Book *a, Book *b) {
    if (a->Rank > b->Rank) {
        return 1;
    } else if (a->Rank < b->Rank) {
        return -1;
    } else {
        return 0;
    }
}
