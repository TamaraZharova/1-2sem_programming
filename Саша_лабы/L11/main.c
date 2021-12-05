// var 0. Book - deleting by Author field, sorting by Rank field
#include "file_functions.h"
#include "UI.h"

#include <stdio.h>

#define OLD_FILE "data/old_file.txt"
#define NEW_FILE "data/new_file.txt"

#define MEDIA_FILE "data/media.txt"

void runTask1(void);

void runTask2(void);

int main(void) {
//    runTask1();
    runTask2();
    return 0;
}

void runTask1(void) {
    String_array* string_array = createFromFile(OLD_FILE);
    if (!string_array) {
        return;
    }
    deleteBlankStr(string_array);
    numberStr(string_array);
    writeToFile(NEW_FILE, string_array);
    freeStrArr(string_array);
}

void runTask2(void) {
    size_t choice = 0;
    while (choice != 5) {
        puts("Choose an action: ");
        puts("1. Add a book;");
        puts("2. Print books;");
        puts("3. Sort books by rank;");
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
}
