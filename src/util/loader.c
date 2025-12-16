// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
// Local headers
#include <loader.h>

ErrorData load_raw(RawInput *raw, const char *name) {
    FILE *inputFile = fopen(name, "r");
    if(inputFile == NULL)
        return CONSTRUCT_ERROR(CHALLENGE_NO_READ, strerror(errno));

    int status;
    status = fseek(inputFile, 0, SEEK_END);
    if(status < 0)
        return CONSTRUCT_ERROR(CHALLENGE_NO_READ, strerror(errno));

    status = ftell(inputFile);
    if(status < 0)
        return CONSTRUCT_ERROR(CHALLENGE_NO_READ, strerror(errno));
    if(status == 0)
        return CONSTRUCT_ERROR(
            CHALLENGE_NO_READ, "Cannot read input file, because size is 0"
        );

    raw->size = (size_t) status;
    status = fseek(inputFile, 0, SEEK_SET);
    if(status < 0)
        return CONSTRUCT_ERROR(CHALLENGE_NO_READ, strerror(errno));

    raw->data = malloc(raw->size + 1);
    if(raw->data == NULL)
        return CONSTRUCT_ERROR(CHALLENGE_NO_MEMORY, "Failed to allocate input data memory");
    size_t bytesRead = fread(raw->data, sizeof(char), raw->size, inputFile);
    if(bytesRead == 0 || feof(inputFile) == 0)
        return CONSTRUCT_ERROR(CHALLENGE_NO_READ, "Failed to read entirety of input file");
    fclose(inputFile);
    raw->data[raw->size] = '\0';
    return emptySuccess;
}

ErrorData find_lines(InputData *input) {
    for(size_t index = 0; index < input->raw.size; index++) {
        if(input->raw.data[index] == '\r')
            input->raw.data[index] = '\0';
        else if(input->raw.data[index] == '\n')
            input->grid.height++;
    }

    input->grid.lines = malloc(sizeof(char*) * input->grid.height);
    if(input->grid.lines == NULL)
        return CONSTRUCT_ERROR(CHALLENGE_NO_MEMORY, "Failed to allocate input data memory");
    size_t gridPosition = 0;
    input->grid.lines[gridPosition++] = input->raw.data;
    for(
        size_t index = 0;
        index < input->raw.size && gridPosition < input->grid.height;
        index++
    ) {
        if(input->raw.data[index] == '\n') {
            input->raw.data[index] = '\0';
            input->grid.lines[gridPosition++] = input->raw.data + index + 1;
        }
    }
    return emptySuccess;
}