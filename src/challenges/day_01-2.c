// C standard headers
#include <stdlib.h>
// Local headers
#include <challenge.h>
#include <feed.h>
#include <stdlib.h>
#include <stdio.h>

const char *dataFileName = "./data/day_01.txt";

ErrorData evaluate(InputData *input, Answer *result) {
    *result = (Answer) { "Password",  0};
    int position = 50;
    

    LineFeed feed = create_linefeed(input);
    for(char *line = get_linefeed(&feed); line != NULL; line = get_linefeed(&feed)) {
        // PROCESS LINE
        int rotations;
        int overflows = 0;
        
        switch(*line) {
            case 'L':
            //subtract value
                rotations = atoi(line + 1);
                int start_pos = position;
                position -= rotations;
                if (position <= 0) {
                    overflows = (-position / 100) + 1;
                    if (start_pos == 0) overflows--;
                }    
                position = (position % 100 + 100) % 100;       
                break;
            case 'R':
                // add value
                rotations = atoi(line + 1);
                position += rotations;
                overflows = position / 100;
                position %= 100;                
                break;

            default:
                    continue;
        }
        result->output += overflows;
        // printf("instruc: %s, - position: %d - overflows: %d \n", line, position, result->output);
    }
    
    return emptySuccess;
}