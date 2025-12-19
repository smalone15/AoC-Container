#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <container.h>

ErrorData evaluate(InputData *input, Answer *result);

extern const char delimiter;
extern const char *dataFileName;

#endif