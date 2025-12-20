#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    char *data;
    size_t size;
} RawInput;

typedef struct {
    char **lines;
    size_t height;
} LineGrid;

typedef struct {
    RawInput raw;
    LineGrid grid;
} InputData;

typedef struct {
    char *name;
    int64_t output;
} Answer;

typedef enum {
    CHALLENGE_SUCCESS,
    CHALLENGE_FAILURE,
    CHALLENGE_NO_MEMORY,
    CHALLENGE_NO_READ,
    CHALLENGE_ENCODING_FAILURE
} ChallengeCode;

typedef struct {
    ChallengeCode code;
    char *info;   
} ErrorData;

extern ErrorData emptySuccess;
extern ErrorData emptyFailure;

#define IS_SUCCESS(_err) (_err.code == CHALLENGE_SUCCESS)
#define IS_FAILURE(_err) (_err.code != CHALLENGE_SUCCESS)
#define CONSTRUCT_ERROR(_code, _info) (ErrorData) { _code, _info }


#endif