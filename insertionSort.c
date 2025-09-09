#include <stdio.h>
#include <string.h>

int main() {
    int arr[] = {5, 2};
    int size = 2;
    int temp = 0;
    for (int i = 1;i<size;i++) {
        for (int j = 0;j<i;j++) {
            if (arr[j]>arr[i]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    for (int i = 0;i<size;i++) {
        printf("%d, ", arr[i]);
    }
    return 0;
}