#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

void convert_to_base(long num, int base) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    
    if (num < 0) {
        putchar('-');
        num = -num;
    }
    
    if (num >= base) {
        convert_to_base(num / base, base);
    }
    putchar(digits[num % base]);
}
