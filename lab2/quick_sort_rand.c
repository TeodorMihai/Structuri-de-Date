#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NMAX 500000

void swap(int *A, int *B) {
    int aux = *A;
    *A = *B;
    *B = aux;
}

void quick_sort(int v[], int st, int dr) {

    int index_pivot = st + rand() % (dr - st);
    int p = v[index_pivot];
    swap(&v[dr], &v[index_pivot]);

    int index = st;

    for(int i = st; i <= dr - 1; ++i)
        if(p > v[i]) {
            swap(&v[i], &v[index]);
            index++;
        }
    swap(&v[dr], &v[index]);
    if(index > st + 1) quick_sort(v, st, index - 1);
    if(index + 1 < dr) quick_sort(v, index + 1, dr);
}

int main() {

    int N; int v[NMAX];

    FILE *in = freopen("algsort.in", "r", stdin);
    FILE *out = freopen("algsort.out", "w", stdout);

    srand(time(NULL));

    scanf("%d", &N);

    for(int i = 1;  i <= N; ++i)
        scanf("%d", &v[i]);
    quick_sort(v, 1, N);

    for(int i = 1; i <= N; ++i)
        printf("%d ", v[i]);

    return 0;
}
