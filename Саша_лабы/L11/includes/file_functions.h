#ifndef LW_11_FILE_FUNCTIONS_H
#define LW_11_FILE_FUNCTIONS_H

#include "string_arrays.h"
#include "media_structs.h"

// Task 1 ---------------------------------------------------------------------

String_array *createFromFile(const char *file_path);
// may return NULL

void writeToFile(const char *file_path, const String_array *string_array);

// Task 2 ---------------------------------------------------------------------

Books_arr *fCreateBooksArr(const char *file_path);

int fWriteBooksArr(const char *file_path, Books_arr *books);

#endif //LW_11_FILE_FUNCTIONS_H
