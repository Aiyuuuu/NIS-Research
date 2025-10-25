#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// A simple enumeration for our state machine to make the code more readable.
enum State { IN_WORD, IN_WHITESPACE };

int main(int argc, char *argv[]) {
    // Counters for our three metrics. Using 'long' to handle larger files.
    long char_count = 0;
    long word_count = 0;
    long line_count = 0;

    // The file pointer for our input source.
    FILE *input_stream = NULL;

    // --- 1. Determine the input source (file or stdin) ---
    if (argc > 2) {
        // The program expects at most one filename.
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    } 
    
    if (argc == 2) {
        // A filename was provided on the command line.
        input_stream = fopen(argv[1], "r");
        if (input_stream == NULL) {
            // perror prints a system error message, which is more informative.
            // e.g., "input.txt: No such file or directory"
            perror(argv[1]);
            return EXIT_FAILURE;
        }
    } else {
        // No filename provided, so we use standard input.
        input_stream = stdin;
    }

    // --- 2. Process the input character by character ---

    int current_char;
    enum State current_state = IN_WHITESPACE; // Assume we start in whitespace.

    // fgetc() returns an int to accommodate the special EOF value.
    while ((current_char = fgetc(input_stream)) != EOF) {
        // Metric 1: Increment character count for every character read.
        char_count++;

        // Metric 2: Increment line count for every newline character.
        if (current_char == '\n') {
            line_count++;
        }

        // Metric 3: Use a state machine to count words.
        // The isspace() function checks for spaces, tabs, newlines, etc.
        if (isspace(current_char)) {
            current_state = IN_WHITESPACE;
        } else {
            // This is a non-whitespace character. If we were previously in
            // whitespace, this marks the beginning of a new word.
            if (current_state == IN_WHITESPACE) {
                word_count++;
            }
            // We are now inside a word.
            current_state = IN_WORD;
        }
    }

    // --- 3. Clean up and print the results ---

    // Close the file if we opened one. We don't close stdin.
    if (input_stream != stdin) {
        fclose(input_stream);
    }
    
    // Print the final counts in a formatted way, similar to the 'wc' utility.
    printf("%8ld %8ld %8ld\n", line_count, word_count, char_count);

    return EXIT_SUCCESS;
}
