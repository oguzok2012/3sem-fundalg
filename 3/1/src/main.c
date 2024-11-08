#include <stdio.h>


void reverseString(char *string, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = temp;
    }
}


char toChar(int digit) {
    if (digit < 10)
        return '0' + digit;
    return 'A' + (digit - 10);
}


void convertToBase2r(int number, int r) {
    unsigned int base = 1 << r;
    unsigned int mask = base - 1;

    int isNegative = 0;
    char string[32];
    int index = 0;

    if (number < 0) {
        isNegative = 1;
        number = -number;
    }

    while (number > 0) {
        unsigned int remainder = number & mask;
        string[index++] = toChar(remainder);
        number >>= r;
    }

    if (isNegative) {
        string[index++] = '-';
    }

    string[index] = '\0';

    reverseString(string, index);
    
    printf("Число в системе счисления с основанием 2^%d: %s\n", r, string);
}

int main() {
    int number = -5;
    int r = 2;

    convertToBase2r(number, r);

    return 0;
}
