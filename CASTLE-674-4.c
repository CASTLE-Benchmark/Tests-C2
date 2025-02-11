#include <stdio.h>

int recursivePrintArray(int* arr, int size, int index) {
    if (index == size) {
        return 0;
    }

    printf("%d\n", arr[index]);
    recursivePrintArray(arr, size, index++);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    recursivePrintArray(arr, 5, 0);
    return 0;
}