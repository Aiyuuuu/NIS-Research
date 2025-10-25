/*
 * count_lwc.c
 *
 * Usage:
 *   ./count_lwc            # read from stdin
 *   ./count_lwc filename   # read from filename
 *
 * Counts:
 *   - Lines: number of newline ('\n')-terminated lines. If the file does not end
 *     with a newline but contains characters, the final line is counted as well.
 *   - Words: sequences of non-whitespace characters separated by space, tab, or newline.
 *   - Characters: total bytes read.
 *
 * Only standard C library functions are used.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    FILE *in = NULL;
    if (argc == 1) {
        in = stdin;
    } else if (argc == 2) {
        in = fopen(argv[1], "r");
        if (in == NULL) {
            fprintf(stderr, "Error: cannot open file '%s'\n", argv[1]);
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long long lines = 0;
    unsigned long long words = 0;
    unsigned long long chars = 0;
    bool in_word = false;
    int c;
    int lastc = EOF;

    while ((c = fgetc(in)) != EOF) {
        ++chars;
        lastc = c;

        if (c == '\n') {
            ++lines;
        }

        /* A word is any sequence of non-whitespace characters separated by
           space, tab, or newline (as specified). We test exactly ' ', '\t', '\n'. */
        if (c != ' ' && c != '\t' && c != '\n') {
            if (!in_word) {
                in_word = true;
                ++words;
            }
        } else {
            in_word = false;
        }
    }

    /* If file had characters but did not end with a newline, count the final line. */
    if (chars > 0 && lastc != '\n') {
        ++lines;
    }

    if (in != stdin) {
        fclose(in);
    }

    /* Print counts in order: lines words characters */
    printf("%llu %llu %llu\n", lines, words, chars);

    return EXIT_SUCCESS;
}

