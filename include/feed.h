#ifndef FEED_H
#define FEED_H

#include <container.h>

typedef struct {
    LineGrid *grid;
    size_t current;
} LineFeed;

LineFeed create_linefeed(InputData *input);
void rewind_linfeed(LineFeed *feed);
void forward_linefeed(LineFeed *feed);
char *get_linefeed(LineFeed *feed);
char *peek_linfeed(LineFeed *feed);

#endif