#include <stdio.h>
#include <string.h>

void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char input1[5];
    char input2[5];

    printf("Enter first string: ");
    fgets(input1, sizeof(input1), stdin);

    // input1[strcspn(input1, "\n")] = '\0';
    // cleanBuffer();

    if (strchr(input1, '\n') == NULL)
        cleanBuffer();
    else
        input1[strcspn(input1, "\n")] = '\0';

    printf("Enter second string: ");
    fgets(input2, sizeof(input2), stdin);
    input2[strcspn(input2, "\n")] = '\0';
    
    printf("First: %s\n", input1);
    printf("Second: %s\n", input2);

    return 0;
}
