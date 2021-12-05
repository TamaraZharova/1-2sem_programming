// var 0. Book - deleting by Author field, sorting by Rank & Name fields
#include "includes/UI.h"

#include <cstdio>

#define MEDIA_FILE "data/media.bin"

int main() {
    size_t choice = 0;
    while (choice != 5) {
        puts("Choose an action: ");
        puts("1. Add a book;");
        puts("2. Print books;");
        puts("3. Sort books;");
        puts("4. Delete books by author;");
        puts("5. Quit;");
        scanf("%zu", &choice);
        puts("");
        switch (choice) {
            case 1:
                addMediaUI(MEDIA_FILE);
                break;
            case 2:
                printMediaUI(MEDIA_FILE);
                break;
            case 3:
                sortMediaUI(MEDIA_FILE);
                break;
            case 4:
                deleteMediaUI(MEDIA_FILE);
                break;
            case 5:
                break;
            default:
                puts("Error occurred: no such action.");
                break;
        }
    }
    return 0;
}
