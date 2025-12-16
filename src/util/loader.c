// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
// Local headers
#include <loader.h>

ErrorData load_raw(InputData *input, const char *name) {
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

    input->size = (size_t) status;
    status = fseek(inputFile, 0, SEEK_SET);
    if(status < 0)
        return CONSTRUCT_ERROR(CHALLENGE_NO_READ, strerror(errno));

    input->rawData = malloc(input->size + 1);
    if(input->rawData == NULL)
        return CONSTRUCT_ERROR(CHALLENGE_NO_MEMORY, "Failed to allocate input data memory");
    size_t bytesRead = fread(input->rawData, sizeof(char), input->size, inputFile);
    if(bytesRead == 0 || feof(inputFile) == 0)
        return CONSTRUCT_ERROR(CHALLENGE_NO_READ, "Failed to read entirety of input file");
    fclose(inputFile);
    input->rawData[input->size] = '\0';
    return emptySuccess;
}

ErrorData find_lines(InputData *input) {
    for(size_t index = 0; index < input->size; index++) {
        if(input->rawData[index] == '\r')
            input->rawData[index] = '\0';
        else if(input->rawData[index] == '\n')
            input->grid.height++;
    }

    input->grid.lines = malloc(sizeof(char*) * input->grid.height);
    if(input->grid.lines == NULL)
        return CONSTRUCT_ERROR(CHALLENGE_NO_MEMORY, "Failed to allocate input data memory");
    size_t gridPosition = 0;
    input->grid.lines[gridPosition++] = input->rawData;
    for(
        size_t index = 0;
        index < input->size && gridPosition < input->grid.height;
        index++
    ) {
        if(input->rawData[index] == '\n') {
            input->rawData[index] = '\0';
            input->grid.lines[gridPosition++] = input->rawData + index + 1;
        }
    }
    return emptySuccess;
}