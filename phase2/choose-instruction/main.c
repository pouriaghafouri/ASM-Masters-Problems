#include <bits/endian.h>
#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
unsigned int tilog2i(unsigned int v) {
    union {
        unsigned int u[2];
        double d;
    } t;

    t.u[__FLOAT_WORD_ORDER == LITTLE_ENDIAN] = 0x43300000; // candidate for emission.
    t.u[__FLOAT_WORD_ORDER != LITTLE_ENDIAN] = v;
    t.d -= 4503599627370496.0;

    return (t.u[__FLOAT_WORD_ORDER == LITTLE_ENDIAN] >> 20) - 0x3FF;
}

unsigned int ailog2i(unsigned int v) {
    int r = 0;
    while (v >>= 1)
        r++;

    return r;
}

int main(void) {
    for (unsigned int v = 1; v < 10000; v++)
        if (tilog2i(v) != ailog2i(v)) 
            printf("Difference at %d\n", v);
    
    return EXIT_SUCCESS;
}
