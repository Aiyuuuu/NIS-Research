/* mywc.c - simple wc-like utility
 *
 * Counts:
 *   - lines   (number of '\n')
 *   - words   (sequences of non-whitespace separated by whitespace)
 *   - bytes   (raw bytes read)
 *
 * Usage:
 *   gcc -std=c11 -O2 -o mywc mywc.c
 *   ./mywc file.txt     # count file
 *   cat file.txt | ./mywc   # read from stdin
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp = stdin;
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 2;
    }

    if (argc == 2) {
        fp = fopen(argv[1], "rb");
        if (!fp) {
            fprintf(stderr, "%s: cannot open '%s': %s\n", argv[0], argv[1], strerror(errno));
            return 1;
        }
    }

    unsigned long long lines = 0;
    unsigned long long words = 0;
    unsigned long long bytes = 0;
    int in_word = 0;

    unsigned char buf[8192];
    size_t nread;
    while ((nread = fread(buf, 1, sizeof buf, fp)) > 0) {
        bytes += (unsigned long long)nread;
        for (size_t i = 0; i < nread; ++i) {
            unsigned char c = buf[i];
            if (c == '\n') lines++;
            if (isspace((int)c)) {
                if (in_word) in_word = 0;
            } else {
                if (!in_word) {
                    words++;
                    in_word = 1;
                }
            }
        }
    }

    if (ferror(fp)) {
        fprintf(stderr, "%s: read error: %s\n", argv[0], strerror(errno));
        if (fp != stdin) fclose(fp);
        return 1;
    }

    if (fp != stdin) fclose(fp);

    /* Output: lines words bytes (in that order) */
    printf("%llu %llu %llu\n", lines, words, bytes);
    return 0;
}

