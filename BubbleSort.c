#include <stdio.h>
#include <stdbool.h>

int main()
{
    int arr[] = {5, 3, 8, 4, 6};
    int size = sizeof(arr)/sizeof(arr[0]);
    bool tried = false;
    int comp = 0;
    int swap = 0;
    int temp;

    for (int i = 0; i < size-1; i++)
    {
        tried = false;
        for (int j = 0; j < size-i-1; j++)
        {
            comp++;
            if (arr[j]>arr[j+1]) {
                tried = true;
                swap++;
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }

        if (tried) {
            break;
        }

        printf("\n");
    }

    for (int i=0;i<size;i++) {
        printf("%d ", arr[i]);
    }
    printf("\nswap:%d, comp:%d", swap, comp);
}