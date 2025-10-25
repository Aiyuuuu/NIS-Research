/* wc_like.c
 * Counts lines, words and characters from a file or stdin.
 * Usage: ./wc_like [filename]
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *fp = stdin;
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 2;
    }

    if (argc == 2) {
        fp = fopen(argv[1], "rb"); /* open binary to count bytes portably */
        if (!fp) {
            perror(argv[1]);
            return 1;
        }
    }

    long long lines = 0;
    long long words = 0;
    long long chars = 0;
    int c;
    int in_word = 0;

    while ((c = fgetc(fp)) != EOF) {
        chars++;
        if (c == '\n') lines++;
        if (isspace((unsigned char)c)) {
            in_word = 0;
        } else {
            if (!in_word) {
                words++;
                in_word = 1;
            }
        }
    }

    if (fp != stdin) fclose(fp);

    /* Print: lines words characters [filename if provided] */
    if (argc == 2)
        printf("%lld %lld %lld %s\n", lines, words, chars, argv[1]);
    else
        printf("%lld %lld %lld\n", lines, words, chars);

    return 0;
}

