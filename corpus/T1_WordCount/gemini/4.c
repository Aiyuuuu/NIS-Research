/**
 * word_count.c
 *
 * A simple C program that mimics the basic functionality of the 'wc' utility.
 * It counts the number of lines, words, and characters in a given input.
 *
 * - If a filename is provided as a command-line argument, it reads from that file.
 * - Otherwise, it reads from standard input (stdin).
 *
 * Compilation:
 *   gcc -Wall -o word_count word_count.c
 *
 * Usage:
 *   ./word_count < file.txt
 *   ./word_count some_document.txt
 *   echo "hello world" | ./word_count
 */

#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS and EXIT_FAILURE
#include <ctype.h>  // For isspace()

// Define constants for the state machine used in word counting
#define IN_WORD  1
#define OUT_WORD 0

int main(int argc, char *argv[]) {
    // Counters for lines, words, and characters
    long line_count = 0;
    long word_count = 0;
    long char_count = 0;

    // The file stream to read from. Defaults to standard input.
    FILE *input_file = stdin;
    const char *filename = NULL;

    // --- Part 1: Determine the input source ---

    if (argc > 2) {
        // The program was called with too many arguments.
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        // A filename was provided. Try to open it.
        filename = argv[1];
        input_file = fopen(filename, "r");

        // Check if the file was opened successfully.
        if (input_file == NULL) {
            // fopen returns NULL on error. perror prints our message
            // followed by the system error message (e.g., "No such file or directory").
            perror(filename);
            return EXIT_FAILURE;
        }
    }

    // --- Part 2: Process the input stream character by character ---

    int current_char;
    int state = OUT_WORD; // Start outside a word

    // Loop until we reach the End-Of-File (EOF) marker.
    // It's crucial that current_char is an `int` to hold the EOF value.
    while ((current_char = fgetc(input_file)) != EOF) {
        // 1. Increment character count for every character read.
        char_count++;

        // 2. Increment line count if the character is a newline.
        if (current_char == '\n') {
            line_count++;
        }

        // 3. Use a state machine to count words.
        // isspace() checks for space, tab, newline, etc.
        if (isspace(current_char)) {
            // If we encounter whitespace, we are "outside" a word.
            state = OUT_WORD;
        } else if (state == OUT_WORD) {
            // If we are "outside" a word and encounter a non-whitespace
            // character, it means a new word has just begun.
            state = IN_WORD;
            word_count++;
        }
    }

    // --- Part 3: Close the file and print the results ---

    // Close the file if it was opened from a command-line argument.
    // We do not close stdin.
    if (input_file != stdin) {
        fclose(input_file);
    }

    // Print the counts in a formatted way, similar to the 'wc' command.
    printf("%8ld %8ld %8ld", line_count, word_count, char_count);

    // If a filename was used, print it after the counts.
    if (filename != NULL) {
        printf(" %s\n", filename);
    } else {
        printf("\n");
    }

    return EXIT_SUCCESS;
}
