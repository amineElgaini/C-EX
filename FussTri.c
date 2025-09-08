#include <stdio.h>
#include <stdbool.h>

void triTableau(int arr[], int n){
    int temp;
    for (int i = 0; i < n - 1 ; i++){
        for (int j = 0; j < n - i - 1 ; j++){
            temp = arr[j];
            if (temp > arr[j+1])
            {
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

bool isTried(int arr[], int size) {
    for (int i = 0; i < size-1 ; i++){
        if (arr[i]>arr[i+1]) {
            return false;
        }
    }
    return true;
}

int main()
{
    int arr1[] = {5,3,5,5, 5, 5};
    int size1 = sizeof(arr1)/sizeof(arr1[0]);
    int arr2[] = {5,6,7,8,8,8,8};
    int size2 = sizeof(arr2)/sizeof(arr1[0]);

    if (!isTried(arr1, size1) || !isTried(arr2, size2)) {
        printf("d");
    }


    int size = size1+size2;
    int fusWithDoub[size];

    int reps = 0;

    for (int i = 0; i < size; i++)
    {
        if (i < size1) {
            fusWithDoub[i] = arr1[i];
        } else {
            fusWithDoub[i] = arr2[i - size1];
        }
    }

    int lastNum = fusWithDoub[0];
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (lastNum == fusWithDoub[i]) {
                break;
            }

            if (fusWithDoub[i]==fusWithDoub[j]) {
                reps++;
            }
        }
        lastNum = fusWithDoub[i];
    }
    int fusWithoutDoub[size-reps];

    lastNum = fusWithDoub[0];
    int fusWithoutDoubIndex = 0;

    for (int i = 0; i < size; i++) {
        if (lastNum == fusWithDoub[i] && fusWithoutDoubIndex != 0) {
            continue;
        } else {
            fusWithoutDoub[fusWithoutDoubIndex] = fusWithDoub[i];
            fusWithoutDoubIndex++;
            lastNum = fusWithDoub[i];
        }
    }

    triTableau(fusWithoutDoub, fusWithoutDoubIndex);

    for (int i = 0; i < fusWithoutDoubIndex; i++)
    {
        printf("%d\n", fusWithoutDoub[i]);
    }

}