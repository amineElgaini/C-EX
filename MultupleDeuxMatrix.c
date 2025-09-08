#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int matrixA[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int matrixB[3][3] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int solution[3][3];

    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            int res = 0;
            for (int k=0;k<3;k++) {
                res += matrixA[i][k] * matrixB[k][j];
            }
            solution[i][j] = res;
        }

    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", solution[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}