/* count.c
   Usage:
     ./count            # read from stdin
     ./count filename   # read from filename

   Prints: <characters> <words> <lines>\n
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    if (argc == 1) {
        fp = stdin;
    } else if (argc == 2) {
        fp = fopen(argv[1], "rb");
        if (!fp) {
            perror("fopen");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long long char_count = 0;
    unsigned long long word_count = 0;
    unsigned long long line_count = 0;

    int in_word = 0; /* 0 = currently in whitespace, 1 = inside a word */
    unsigned char buf[8192];
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) {
        for (size_t i = 0; i < n; ++i) {
            unsigned char ch = buf[i];
            /* count characters (bytes) */
            ++char_count;
            /* count lines on newline character */
            if (ch == '\n') ++line_count;
            /* use isspace on unsigned char cast */
            if (isspace((int)ch)) {
                in_word = 0;
            } else {
                if (!in_word) {
                    ++word_count;
                    in_word = 1;
                }
            }
        }
    }

    if (fp != stdin) fclose(fp);

    /* print counts in order: characters words lines */
    printf("%llu %llu %llu\n", char_count, word_count, line_count);
    return EXIT_SUCCESS;
}

