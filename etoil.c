int main()
{
    int x = 5;
    for (int i=0; i<x; i++) {
        for (int j=0; j<(x*2)-1; j++) {
            if (i==j || j==(((x*2)-2)-i)) {
                printf("*");
            } else {
                printf(" ");   
            }
        }
        printf("\n");
    }
    return 0;
}