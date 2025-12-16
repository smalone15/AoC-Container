#ifndef LOADER_H
#define LOADER_H

#include <container.h>

ErrorData load_raw(RawInput *raw, const char *name);
ErrorData find_lines(InputData *input);

#endif