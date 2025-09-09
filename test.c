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
int main() {
    // int arr1[] = {1,5,6};
    // int arr2[] = {3,4,5};
    int arr1[] = {1,5,6};
    int arr2[] = {7,8,9};
    int sol[6] = {0};
    merge(sol, arr1, 3, arr2, 3);
    printf("\n\n");
    for (int i=0;i<6;i++) {
        printf("%d, ", sol[i]);
    }
    return 0;
}