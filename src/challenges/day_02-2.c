// C standard headers
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
// Local headers
#include <challenge.h>
#include <feed.h>

const char delimiter = ',';
const char *dataFileName = "./data/day_02.txt";

#define TEXT_LEN 256

static bool get_range(const char *line, int64_t *start, int64_t *end);
static bool is_duplicate(const char *numberText, int length);

ErrorData evaluate(InputData *input, Answer *result) {
    *result = (Answer) { "Sum of invalid ID's", 0 };

    LineFeed feed = create_linefeed(input);
    for(char *line = get_linefeed(&feed); line != NULL; line = get_linefeed(&feed)) {
        int64_t start, end;
        if(get_range(line, &start, &end)) continue;
        char numberText[TEXT_LEN];
        for(int64_t i = start; i <= end; i++) {
            int status = snprintf(numberText, TEXT_LEN, "%lld", i);
            if(status < 0)
                return CONSTRUCT_ERROR(
                    CHALLENGE_ENCODING_FAILURE,
                    "Failed to encode number to text conversion"
                );
            if(status >= TEXT_LEN)
                return CONSTRUCT_ERROR(
                    CHALLENGE_ENCODING_FAILURE,
                    "Converted number had length too great for buffer"
                );
            if(is_duplicate(numberText, status))
                result->output += i;
        }
    }
    return emptySuccess;
}

static bool get_range(const char *line, int64_t *start, int64_t *end) {
    char *middle = strchr(line, '-');
    if(middle == NULL) return true;
    *start = atoll(line);
    *end = atoll(middle + 1);
    return false;
}

static bool is_duplicate(const char *numberText, int length) {
    // numberText - string of number value to check (numberText = "1212")
    // digit length of value to check "1212" (length = 4)"
    
    // Example number "1212"
    
    if(length <= 1) return false; // if check does not trigger because longer than 1
    for(int pattern = 1; pattern <= length / 2; pattern++) { // loop 1, pattern "1" | loop 2 pattern "12"
        if(length % pattern != 0) continue;  // if pattern length modulo is not 0, leave loop as failure
        
        bool match = true;  // set bool for failure case
        for(int i = pattern; i < length; i++) {  // iterate through length of patterns as long as iterator is less than length for checking pattern
            if(numberText[i] != numberText[i % pattern]) {  // numberText[i] in first loop, "1" ### 
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}