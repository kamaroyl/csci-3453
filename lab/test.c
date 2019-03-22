#include <time.h>
#include <stdio.h>
#include <stdlib.h>



int main() {
    char a[12] = "84508.45";
    long test = atol(a);
    printf("%ld\n", test);
    return 0;
}
