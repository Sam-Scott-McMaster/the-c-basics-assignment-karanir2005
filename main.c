#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

#define DEFAULT_BASE 16
#define MIN_BASE 2
#define MAX_BASE 36

void help_msg(){
    printf("Developed by Rushil Karani.\n\n");

    printf("Usage: convert [-b BASE] [-r START FINISH]\n");
    printf("  The convert utility reads integers from user or a specified range\n");
    printf("  and converts them to a new base (default base: 16). The result is printed.\n\n");
    
    printf("  -b BASE          Base for conversion: (default is 16, hexadecimal).\n");
    printf("                   Valid base values: 2 to 36.\n");
    printf("                   Digits 10-35 are denoted with letters A-Z.\n");
    printf("  -r START FINISH  Convert all numbers in range [START, FINISH].\n");
    printf("                   Otherwise, numbers will be read from user input one at a time.\n");
    printf("                   Enter Ctrl+D to end.\n\n");
    
    printf("Enter only integer values to convert.\n");
}

void parse_args(int argc, char *argv[], int *base, long *start, long *finish, int *range_mode) {
    *base = DEFAULT_BASE;
    *range_mode = 0;

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            *base = atoi(argv[++i]);
            if (*base < MIN_BASE || *base > MAX_BASE) {
                fprintf(stderr, "Usage: convert [-b BASE] [-r START FINISH]\n");
                fprintf(stderr, "       1 < BASE < 37\n");
                fprintf(stderr, "       START and FINISH are long integers\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "-r") == 0 && i + 2 < argc) {
            *start = atol(argv[++i]);
            *finish = atol(argv[++i]);
            *range_mode = 1;
        } else {
            fprintf(stderr, "Usage: convert [-b BASE] [-r START FINISH]\n");
            fprintf(stderr, "       1 < BASE < 37\n");
            fprintf(stderr, "       START and FINISH are long integers\n");
            
            exit(1);
        }
    }
}

void display_range(long start, long finish, int base) {
    for (long i = start; i <= finish; i++) {       
        convert_to_base(i, base);
        printf("\n");
    }
}

void read_input(int base) {
    long number;
               
    int result=1;   
    
    while (result==1) {
      
        result = scanf("%ld", &number);
        if (result==0){
            fprintf(stderr, "Error: Non-long-int token encountered.\n");         
            exit(1);
        }
        else if (result==1){
            convert_to_base(number, base);
            printf("\n");
        }
    }    
}

int main(int argc, char *argv[]) {

    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        help_msg();
        return 0;
    }

    int base;
    long start = 0, finish = 0;
    int range_mode;

    parse_args(argc, argv, &base, &start, &finish, &range_mode);

    if (range_mode) {
        display_range(start, finish, base);
    } else {
        read_input(base);
    }

    return 0;
}



