#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

/*
Rushil Karani
recursive function that outputs one character at a time, 
converting the decimal number to a specifies base.
*/

// function to convert number to a given base
void convert_to_base(long num, int base) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";  // characters for digits

    // handle negative numbers
    if (num < 0) {
        printf("-");  // print minus sign
        num = -num;   // convert to positive
    }

    // recursively convert the number
    if (num >= base) {
        convert_to_base(num / base, base);  // call recursively for the quotient
    }
    printf("%c", digits[num % base]);  // print the remainder as the base digit
}
