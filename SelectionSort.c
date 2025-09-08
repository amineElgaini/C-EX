#include <stdio.h>
#include <string.h>

int main() {
    int nums[] = {0,4,3,2,1};
    for (int i= 0;i<5;i++) {
        for (int j=i+1;j<5;j++) {
            if (nums[i]>nums[j]){
                int temp = nums[i];
                nums[i]=nums[j];
                nums[j]=temp;
            }
        }
    }

    for (int i= 0;i<5;i++) {
        printf("%d,", nums[i]);
    }
}