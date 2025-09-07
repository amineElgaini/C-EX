#include <stdio.h>
#include <stdbool.h>

int main() {
  int arr[] = {5, 12, 18, 23, 27, 31, 36, 42, 47, 53, 59, 64, 70, 75, 81, 88, 94, 99, 105, 112};
  int num = 112;

  int size = (sizeof(arr)/sizeof(int));
  int end = size-1;
  int start = 0;
  int midIndex, midVal;

  while (true)
  {
    midIndex = (end + start) / 2;
    midVal = arr[midIndex];

    if (midVal == num) {
      printf("F%d\n", midIndex);
      break;

    } else if (start == end) {
      printf("not%dfound\n", midIndex);
      break;

    } else if (num < midVal) {
      printf("b%dig\n", midIndex);
      end = midIndex-1;

    } else if (num > midVal) {
      printf("s%dm\n", midIndex);
      start = midIndex+1;
    }
  }
  
  return 0;
}