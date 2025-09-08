#include <stdio.h>

int main() {
  int arr1[] = {1, 2, 3, 4, 5};
  int size = 5;
  int dec = 6;
  int temp1 = 0;
  int temp2 = 0;
  
  for(int i = 0; i<dec; i++) {
    temp1 = arr1[0];
    for(int i = 0; i<size-1; i++) {
      temp2 = arr1[i+1];
      arr1[i+1] = temp1;
      temp1=temp2;
    }
    arr1[0]=temp1;
  }

  for(int i = 0; i<size; i++) {
    printf("%d,", arr1[i]);
  }

  return 0;
}
