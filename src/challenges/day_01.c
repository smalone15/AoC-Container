// Local headers
#include <challenge.h>
#include <feed.h>

const char *dataFileName = "./data/day_01.txt";

ErrorData evaluate(InputData *input, Answer *result) {
    LineFeed feed = create_linefeed(input);
    for(char *line = get_linefeed(&feed); line != NULL; line = get_linefeed(&feed)) {
        // PROCESS LINE
    }
    *result = (Answer) { "TestObject", 100 };
    return emptySuccess;
}