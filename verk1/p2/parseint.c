#include "parseint.h"

/*
 * Returns the value of c or -1 on error
 */
int convertDecimalDigit(char c)
{
    (void)c;
    int convertToInt = c - '0';
    if (convertToInt >= 0 && convertToInt <= 9) {
      return convertToInt;
    }
    return -1;
}

/*
 * Parses a non-negative integer, interpreted as octal when starting with 0,
 * decimal otherwise. Returns -1 on error.
 */
int parseInt(char *string)
{
    (void)string;
    int result = 0;
    int base = 10;

    // Check if given string has a leading 0, making it an octal number.
    if (*string == '0') {
       base = 8;
       // Move past the 0 by incrementing the pointer by 1.
       string++;
    }

    // Run until we reach the end of the string which is indicated by \0.
    while (*string != '\0') {
       // Convert the digit were parsing to an integer
       int convertToInt = convertDecimalDigit(*string);

       // Return -1 on error converting
       if (convertToInt == -1 || convertToInt >= base) {
         return -1;
       }

       // Shift result by our base and add the converted digit.
       result = result * base + convertToInt;
       string++;
    }

    return result;
}
