#include "super/io.h"
#include <stdlib.h>
#include <stdio.h>


char* stream(const char* filepath)
{
    char* buffer = 0;
    long length;

    FILE* file = fopen(filepath, "rb");

    if (!file) {
        printf("Error reading file %s\n", filepath);
        exit(2);
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);

    fseek(file, 0, SEEK_SET);

    buffer = calloc(length, length);

    if (buffer) fread(buffer, 1, length, file);

    fclose(file);

    return buffer;
}
