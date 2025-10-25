/**
 * @file wc_c.c
 * @brief A C program to count lines, words, and characters.
 *
 * This program mimics the basic functionality of the Unix `wc` utility.
 * It reads from a file specified as a command-line argument or from
 * standard input if no file is provided.
 *
 * It calculates and prints the total number of lines, words, and
 * characters.
 *
 * - A line is defined by the newline character '\n'.
 * - A word is a sequence of non-whitespace characters separated by
 *   whitespace (space, tab, newline, etc., as defined by isspace()).
 *
 * Compilation:
 *   gcc -Wall -Wextra -std=c11 -o wc_c wc_c.c
 *
 * Usage:
 *   ./wc_c < my_file.txt
 *   ./wc_c my_file.txt
 *   echo "hello world" | ./wc_c
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// A structure to hold the three counts.
// Using a struct makes the code cleaner than passing multiple pointers.
typedef struct {
    unsigned long long lines;
    unsigned long long words;
    unsigned long long chars;
} Counts;

/**
 * @brief Processes a file stream to count lines, words, and characters.
 * @param fp A pointer to a valid FILE stream to be read.
 * @return A Counts struct containing the final totals.
 */
Counts count_stats(FILE *fp) {
    Counts counts = {0, 0, 0};
    int c;

    // A simple state machine to track if we are inside or outside a word.
    enum {
        IN_WORD,
        OUT_WORD
    } state = OUT_WORD;

    // fgetc returns an int to accommodate EOF.
    while ((c = fgetc(fp)) != EOF) {
        counts.chars++;

        if (c == '\n') {
            counts.lines++;
        }

        // isspace() from <ctype.h> correctly handles space, tab, newline, etc.
        if (isspace(c)) {
            state = OUT_WORD;
        } else {
            // If we are moving from being outside a word to inside a word,
            // we have found the beginning of a new word.
            if (state == OUT_WORD) {
                counts.words++;
            }
            state = IN_WORD;
        }
    }

    return counts;
}

int main(int argc, char *argv[]) {
    FILE *input_stream = stdin; // Default to standard input

    // Check command-line arguments to see if a filename was provided.
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        // A filename was provided, try to open it for reading.
        input_stream = fopen(argv[1], "r");
        if (input_stream == NULL) {
            // Use perror for system errors; it's more informative.
            // It prints our message, a colon, and the system error message.
            perror(argv[1]);
            return EXIT_FAILURE;
        }
    }

    // Perform the counting.
    Counts final_counts = count_stats(input_stream);

    // If we opened a file, we must close it.
    // Do not close stdin.
    if (input_stream != stdin) {
        fclose(input_stream);
    }

    // Print the results in the standard "wc" format.
    // %llu is the format specifier for unsigned long long.
    printf("%llu %llu %llu\n", final_counts.lines, final_counts.words, final_counts.chars);

    return EXIT_SUCCESS;
}
