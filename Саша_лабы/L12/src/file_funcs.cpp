#include "../includes/file_funcs.h"

#include <sys/stat.h>
#include <unistd.h>

size_t countElements(FILE *file, size_t size) {
    struct stat buff = {};
    fstat(fileno(file), &buff);

    size_t counter = buff.st_size / size;
    return counter;
}
