#include <stdio.h>

#define ZERO 3

int main() {
    int input = 0;

    printf("Enter input: ");
    scanf("%d", &input);

    printf("Result: %d\n", input / ZERO);

    return 0;
}