#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int gt (const void * l, const void * r) {
    return *(uint32_t*)l - *(uint32_t*)r;
}

int main() {
    size_t n;
    scanf("%lu", &n);
    uint32_t * holes = malloc(n*sizeof(uint32_t));
    for(size_t i = 0; i < n; ++i) {
        scanf("%d", holes+i);
    }
    qsort(holes, n, sizeof(uint32_t), gt);
    uint32_t n_pairs, n_nuts;
    scanf("%d %d", &n_pairs, &n_nuts);

    uint32_t l = 0;
    uint32_t r = n-1;
    uint32_t found_pairs = 0;

    while (l < r) {
        int32_t pair = n_nuts - holes[l] - holes[r];
        if (pair == 0) {
            ++found_pairs;
            ++l;
        } else if (pair > 0) {
            ++l;
        } else if(pair < 0) {
            --r;
        }
    }

    if(found_pairs >= n_pairs) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}