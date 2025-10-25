#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// Function to analyze the text stream and print statistics
void analyze_text(FILE *stream) {
    unsigned long lines = 0;
    unsigned long words = 0;
    unsigned long characters = 0;
    bool in_word = false;
    int c;

    // Read the stream character by character until End Of File (EOF)
    while ((c = fgetc(stream)) != EOF) {
        characters++;

        // Count lines: increment on every newline character
        if (c == '\n') {
            lines++;
        }

        // Count words: A word is a sequence of non-whitespace characters.
        // We detect the *start* of a new word by checking if the current
        // character is NOT whitespace and we were NOT previously in a word.
        if (isspace(c)) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            words++;
        }
    }

    // Print the three statistics separated by spaces
    printf("%lu %lu %lu\n", lines, words, characters);
}

int main(int argc, char *argv[]) {
    // 1. Check if a filename was provided as a command-line argument
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        analyze_text(file);
        fclose(file);
    } 
    // 2. If no arguments, read from Standard Input (typing or piped text)
    else {
        analyze_text(stdin);
    }

    return 0;
}
