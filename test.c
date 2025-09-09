#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char ch[50] = "amin e";
    char sh[50] = "amine";

    int comp = abs(strlen(ch)-strlen(sh));
    
    int i = 0, j = 0;

    while (i<strlen(ch) && j<strlen(sh)) {
        if (ch[i]==sh[j]) {
            i++;
            j++;
        } else if (ch[i]==' ' || sh[j]==' ') {
            comp--;
            if (ch[i]==' ')
                i++;

            if (sh[j]==' ')
                j++;
        }
    }
    printf("%d", comp);
}