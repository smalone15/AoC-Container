#ifndef CONTAINER_H
#define CONTAINER_H

#include <stddef.h>

typedef struct {
    char *rawData;
    size_t size;
    struct {
        char **lines;
        size_t height;
    } grid;
} InputData;

typedef struct {
    char *name;
    int output;
} Answer;

typedef enum {
    CHALLENGE_SUCCESS,
    CHALLENGE_FAILURE,
    CHALLENGE_NO_MEMORY
} ChallengeCode;

typedef struct {
    ChallengeCode code;
    char *info;   
} ErrorData;

extern ErrorData emptySuccess;
extern ErrorData emptyFailure;

#define IS_SUCCESS(_err) (_err.code == CHALLENGE_SUCCESS)
#define IS_FAILURE(_err) (_err.code != CHALLENGE_SUCCESS)

#endif