#include <stdio.h>
#include <stdlib.h>

void funct(int y, int x) {

    int i;
    for(i = 0 ;i < x; ++i)
        printf("%d", i);
}

int main() {

    int x;
    scanf("%d", &x);
    ++x;
    funct(x , 7);
    printf("%d", x);

    return 0;
}
