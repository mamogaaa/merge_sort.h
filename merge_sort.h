#include <string.h>

void merge(void* a, void* b,
    size_t alen, size_t blen, size_t size, int (*comp)(const void*, const void*)) {
    size_t i = 0, j = 0, k = 0;
    void* result = malloc((alen + blen) * size);
    while (i < alen || j < blen) {
        if (i < alen && j < blen) {
            if (comp(a + i * size, b + j * size) < 1) {
                memcpy(result + k * size, a + i * size, size);
                k++;
                i++;
            } else {
                memcpy(result + k * size, b + j * size, size);
                k++;
                j++;
            }
        } else if (i < alen) {
            memcpy(result + k * size, a + i * size, size);
            k++;
            i++;
        } else if (j < alen) {
            memcpy(result + k * size, b + j * size, size);
            k++;
            j++;
        }
    }
    memcpy(a, result, (alen + blen) * size);
    free(result);
}

void merge_sort(void* arr, size_t count, size_t size, int (*comp)(const void*, const void*)) {
    if (count <= 1) return;
    void* left = arr;
    void* right = arr + count / 2 * size;
    size_t llen = count / 2;
    size_t rlen = count - count / 2;
    merge_sort(left, llen, size, comp);
    merge_sort(right, rlen, size, comp);
    merge(left, right, llen, rlen, size, comp);
}
