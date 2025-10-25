/**
 * @file my_wc.c
 * @brief A self-contained C program that mimics the classic 'wc' utility.
 *
 * This program counts the number of lines, words, and bytes in a given
 * input. The input can be a file specified as a command-line argument or
 * standard input if no file is provided.
 *
 * A "word" is defined as any sequence of characters separated by whitespace
 * (as determined by the isspace() function).
 *
 * Compilation:
 *   gcc -Wall -o my_wc my_wc.c
 *
 * Usage:
 *   ./my_wc [filename]
 *   cat somefile.txt | ./my_wc
 */

#include <stdio.h>
#include <stdlib.h> // For EXIT_FAILURE, EXIT_SUCCESS
#include <ctype.h>  // For isspace()

// A structure to hold the three counts
typedef struct {
    long lines;
    long words;
    long bytes;
} Counts;

// Function prototype
Counts count_stats(FILE *stream);

int main(int argc, char *argv[]) {
    FILE *input_stream = NULL;
    const char *filename = "";

    // --- Step 1: Determine the input source ---
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    } else if (argc == 2) {
        // A filename is provided as an argument
        filename = argv[1];
        input_stream = fopen(filename, "r");
        if (input_stream == NULL) {
            // perror prints a system error message, e.g., "No such file or directory"
            perror(filename);
            return EXIT_FAILURE;
        }
    } else {
        // No arguments, so read from standard input
        input_stream = stdin;
    }

    // --- Step 2: Perform the counting ---
    Counts counts = count_stats(input_stream);

    // --- Step 3: Print the results ---
    // The format "%8ld" prints a long integer, padded with spaces to 8 characters.
    printf("%8ld %8ld %8ld", counts.lines, counts.words, counts.bytes);
    if (argc == 2) {
        // Print the filename if one was provided
        printf(" %s\n", filename);
    } else {
        printf("\n");
    }

    // --- Step 4: Clean up ---
    // Only close the file if it's not stdin
    if (input_stream != stdin) {
        fclose(input_stream);
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Reads from a stream and counts lines, words, and bytes.
 *
 * @param stream The input stream (e.g., a file or stdin).
 * @return A Counts struct containing the final counts.
 */
Counts count_stats(FILE *stream) {
    Counts c = {0, 0, 0};
    int current_char;
    int in_word = 0; // State flag: 0 = not in a word, 1 = in a word

    // The loop reads one character at a time until the end of the file (EOF)
    // Note: 'current_char' must be an 'int' to correctly handle the EOF value.
    while ((current_char = fgetc(stream)) != EOF) {
        // 1. Count bytes (characters)
        c.bytes++;

        // 2. Count lines
        if (current_char == '\n') {
            c.lines++;
        }

        // 3. Count words using a simple state machine
        if (isspace(current_char)) {
            // If we encounter whitespace, we are no longer in a word.
            in_word = 0;
        } else {
            // If we encounter a non-whitespace character and we were *not*
            // previously in a word, it means a new word has just started.
            // We count it and set the flag.
            if (in_word == 0) {
                c.words++;
                in_word = 1; // We are now in a word
            }
        }
    }

    return c;
}
