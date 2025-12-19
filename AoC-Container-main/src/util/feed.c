// Local headers
#include <feed.h>

LineFeed create_linefeed(InputData *input) {
    return (LineFeed) { &input->grid, 0 };
}

void rewind_linfeed(LineFeed *feed) {
    feed->current = 0;
}

void forward_linefeed(LineFeed *feed) {
    feed->current = feed->grid->height - 1;
}

char *get_linefeed(LineFeed *feed) {
    if(feed->current > feed->grid->height - 1)
        return NULL;
    return feed->grid->lines[feed->current++];
}

char *peek_linfeed(LineFeed *feed) {
    return feed->grid->lines[feed->current];
}