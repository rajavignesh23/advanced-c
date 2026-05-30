#include <stdio.h>
#include <stdlib.h>

void rearrange(int *arr, int size) {
    int *temp = (int *)malloc(size * sizeof(int));

    int *p = arr;
    int *t = temp;

    while(p < arr + size) {
        if(*p % 2 == 0) {
            *t = *p;
            t++;
        }
        p++;
    }

    p = arr;

    while(p < arr + size) {
        if(*p % 2 != 0) {
            *t = *p;
            t++;
        }
        p++;
    }

    p = arr;
    t = temp;

    while(p < arr + size) {
        *p = *t;
        p++;
        t++;
    }

    free(temp);
}

int main() {
    int arr[] = {10,9,8,7,6,5,4,3,2,1};
    int size = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, size);

    printf("Rearranged array:\n");

    int *p = arr;

    while(p < arr + size) {
        printf("%d ", *p);
        p++;
    }

    return 0;
}