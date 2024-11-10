#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

#define DEFAULT_BASE 16
#define MIN_BASE 2
#define MAX_BASE 36

/*
Rushil Karani
main file of the convert utility
functions: reading input, read user input, and read range and call the recursive function.
*/

void help_msg(){
    // print program info
    printf("Developed by Rushil Karani.\n\n");

    // print usage instructions
    printf("Usage: convert [-b BASE] [-r START FINISH]\n");
    printf("  The convert utility reads integers from user or a specified range\n");
    printf("  and converts them to a new base (default base: 16). The result is printed.\n\n");
    
    // print base conversion info
    printf("  -b BASE          Base for conversion: (default is 16, hexadecimal).\n");
    printf("                   Valid base values: 2 to 36.\n");
    printf("                   Digits 10-35 are denoted with letters A-Z.\n");
    // print range info
    printf("  -r START FINISH  Convert all numbers in range [START, FINISH].\n");
    printf("                   Otherwise, numbers will be read from user input one at a time.\n");
    printf("                   Enter Ctrl+D to end.\n\n");
    
    // general input info
    printf("Enter only integer values to convert.\n");
}

void parse_args(int argc, char *argv[], int *base, long *start, long *finish, int *range_mode) {
    *base = DEFAULT_BASE;  // set default base
    *range_mode = 0;       // set default mode to single input

    // loop through arguments
    for (int i = 1; i < argc; i++) {

        // handle base argument
        if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            *base = atoi(argv[++i]);  // set base
            // check if base is valid
            if (*base < MIN_BASE || *base > MAX_BASE) {
                // print error message and exit
                fprintf(stderr, "Usage: convert [-b BASE] [-r START FINISH]\n");
                fprintf(stderr, "       1 < BASE < 37\n");
                fprintf(stderr, "       START and FINISH are long integers\n");
                exit(1);
            }
        } 
        // handle range argument
        else if (strcmp(argv[i], "-r") == 0 && i + 2 < argc) {
            *start = atol(argv[++i]);  // set start
            *finish = atol(argv[++i]); // set finish
            *range_mode = 1;            // set range mode
        } 
        // invalid arguments
        else {
            // print error message and exit
            fprintf(stderr, "Usage: convert [-b BASE] [-r START FINISH]\n");
            fprintf(stderr, "       1 < BASE < 37\n");
            fprintf(stderr, "       START and FINISH are long integers\n");
            exit(1);
        }
    }
}

void display_range(long start, long finish, int base) {
    // loop through range
    for (long i = start; i <= finish; i++) {       
        convert_to_base(i, base);  // convert number to base
        printf("\n");
    }
}

void read_input(int base) {
    long number;  // variable for user input
               
    int result = 1;  // flag to check scanf result
    
    // loop for reading user input
    while (result == 1) {
      
        result = scanf("%ld", &number);  // read number
        // handle invalid input
        if (result == 0) {
            fprintf(stderr, "Error: Non-long-int token encountered.\n");         
            exit(1);  // exit on error
        }
        // process valid input
        else if (result == 1) {
            convert_to_base(number, base);  // convert number to base
            printf("\n");
        }
    }    
}

int main(int argc, char *argv[]) {

    // check for help argument
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        help_msg();  // print help message
        return 0;
    }

    int base;
    long start = 0, finish = 0;
    int range_mode;

    // parse command line arguments
    parse_args(argc, argv, &base, &start, &finish, &range_mode);

    // process range or user input
    if (range_mode) {
        display_range(start, finish, base);
    } else {
        read_input(base);
    }

    return 0;
}
