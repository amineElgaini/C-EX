#include <stdio.h>
#include <string.h>

void merge(int mergedArr[], int arr1[], int size1, int arr2[], int size2) {
    
    int rechedIndexInSecondArr = 0, rechedIndexInMergedArr = 0;
    int secondEnded = 0, firstEnded = 0;

    for (int i=0;i<size1;i++) {
        if (secondEnded==0) {
            for (int j=rechedIndexInSecondArr;j<size2;j++) {
                if (!firstEnded) {
                    if (arr1[i]<=arr2[j]) {
                        mergedArr[rechedIndexInMergedArr++] = arr1[i];
    
                        if (i==size1-1)
                            firstEnded = 1;
                        else
                            break;
                    } else {
                        rechedIndexInSecondArr++;
                        mergedArr[rechedIndexInMergedArr++] = arr2[j];
                    }
    
                    if (j==size2-1)
                        secondEnded = 1;
                }
                if (firstEnded)
                    mergedArr[rechedIndexInMergedArr++] = arr2[j];
            }
        }
        if (secondEnded==1)
            mergedArr[rechedIndexInMergedArr++] = arr1[i];
    }
}

void mergeSort(int arr[], int size) {
    if (size!=1) {
        int arr1[size/2], arr2[size-(size/2)];
        for(int i=0;i<size;i++) {
                if (i<=size/2)
                    arr1[i];
                else
                    arr2[i];
        }
        mergeSort(arr1, size/2);
        mergeSort(arr2, size-(size/2));
    } else {
        merge();
    }
}

int main() {
    int arr[]={5,4,3 ,1, 5,9};
    mergeSort(arr, 6);

    for (int i=0;i<6;i++) {
        printf("%d, ", arr[i]);
    }
    return 0;
}