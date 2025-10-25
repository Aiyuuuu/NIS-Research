/* textstats.c
 * Count lines, words and characters from a file or stdin.
 * Usage:
 *   gcc -std=c11 -O2 -o textstats textstats.c
 *   ./textstats filename.txt   # read from file
 *   ./textstats                # read from stdin (type, then EOF: Ctrl-D on Unix, Ctrl-Z on Windows)
 *
 * Note: lines are counted by the number of '\n' characters.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *in = stdin;
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        in = fopen(argv[1], "rb");
        if (!in) {
            perror("fopen");
            return 1;
        }
    }

    unsigned long long lines = 0;
    unsigned long long words = 0;
    unsigned long long chars = 0;
    int c;
    int in_word = 0;

    while ((c = fgetc(in)) != EOF) {
        chars++;
        if (c == '\n') lines++;
        if (isspace((unsigned char)c)) {
            if (in_word) {
                words++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }

    /* If file ended while inside a word, count that word */
    if (in_word) words++;

    if (in != stdin) fclose(in);

    /* Output: lines words characters (simple, space-separated) */
    printf("%llu %llu %llu\n", lines, words, chars);
    return 0;
}

