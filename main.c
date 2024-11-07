#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

#define DEFAULT_BASE 16
#define MIN_BASE 2
#define MAX_BASE 36

void parse_args(int argc, char *argv[], int *base, long *start, long *finish, int *range_mode) {
    *base = DEFAULT_BASE;
    *range_mode = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            *base = atoi(argv[++i]);
            if (*base < MIN_BASE || *base > MAX_BASE) {
                fprintf(stderr, "Usage: convert [-b BASE] [-r START FINISH]\n1 < BASE < 37\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "-r") == 0 && i + 2 < argc) {
            *start = atol(argv[++i]);
            *finish = atol(argv[++i]);
            *range_mode = 1;
        } else {
            fprintf(stderr, "Usage: convert [-b BASE] [-r START FINISH]\n1 < BASE < 37\n");
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    int base;
    long start = 0, finish = 0;
    int range_mode;

    parse_args(argc, argv, &base, &start, &finish, &range_mode);

    if (range_mode) {
        for (long i = start; i <= finish; i++) {
            printf("%ld in base %d: ", i, base);
            convert_to_base(i, base);
            printf("\n");
        }
    } else {
        long number;
        printf("Enter numbers to convert (Ctrl-D to end):\n");
        while (scanf("%ld", &number) != EOF) {
            printf("%ld in base %d: ", number, base);
            convert_to_base(number, base);
            printf("\n");
        }
    }

    return 0;
}
