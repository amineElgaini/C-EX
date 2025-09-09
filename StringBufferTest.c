#include <stdio.h>
#include <string.h>

void cleanBuffer(char input[]) {
    if (strchr(input, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    else {

        input[strcspn(input, "\n")] = '\0';
    }
}

int main() {
    char input1[5];
    char input2[5];

    printf("Enter first string: ");
    fgets(input1, sizeof(input1), stdin);

    cleanBuffer(input1);

    printf("Enter second string: ");
    fgets(input2, sizeof(input2), stdin);
    input2[strcspn(input2, "\n")] = '\0';
    
    printf("First: %s\n", input1);
    printf("Second: %s\n", input2);

    return 0;
}
