#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid inputs.");
    }
    int x1 = atoi(argv[1]);
    int x2 = atoi(argv[2]);
    x1 > x2 ? printf("The max is: %d\n", x1)
    : printf("The max is: %d\n", x2);
    return 0;
}
#pragma clang diagnostic pop