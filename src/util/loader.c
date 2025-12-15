// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// Local headers
#include <loader.h>

ErrorData load_raw(InputData *input, const char *name) {
    FILE *inputFile = fopen(name, "r");
    // HANDLE FAIL
    fseek(inputFile, 0, SEEK_END);
    // HANDLE FAIL
    input->size = (size_t) ftell(inputFile);
    // HANDLE FAIL
    // HANDLE SIZE == 0
    fseek(inputFile, 0, SEEK_SET);
    // HANDLE FAIL
    input->rawData = malloc(input->size + 1);
    // HANDLE FAIL
    fread(input->rawData, sizeof(char), input->size, inputFile);
    // HANDLE FAIL
    fclose(inputFile);
    input->rawData[input->size] = '\0';
}

ErrorData find_lines(InputData *input) {
    for(size_t index = 0; index < input->size; index++) {
        if(input->rawData[index] == '\r')
            input->rawData[index] = '\0';
        else if(input->rawData[index] == '\n')
            input->grid.height++;
    }

    input->grid.lines = malloc(sizeof(char*) * input->grid.height);
    // HANDLE FAIL
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
}