#ifndef LW_12_STRUCTS_H
#define LW_12_STRUCTS_H

#define FIELD_LEN 255

typedef struct {
    char Name[FIELD_LEN];
    char Author[FIELD_LEN];
    int PageCount;
    int Rank;
} Book;

void readBook(Book *book);

void printBook(Book *book);

int cmpBookName(Book *a, Book *b);

int cmpBookRank(Book *a, Book *b);

#endif //LW_12_STRUCTS_H
