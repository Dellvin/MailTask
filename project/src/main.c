#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <sched.h>
#include "libIZ2_dymamic.h"
#include "IZ2_STATIC.h"



int main() {
    int64_t *arr;
    size_t size = 10000;
    arr = (int64_t *) malloc(size * sizeof(int64_t));
    if (!arr) return 0;
    for (size_t i = 0; i < size; ++i) {
        arr[i] = i;
    }

    int64_t *answer;
    clock_t start;
    start = clock();
    answer=sumNotEvenThread(arr, size);
    if (!answer) {
        free(arr);
        return 0;
    }
    printf("Answer with thread NOT even: %ld\n", *answer);
    free(answer);
    answer=sumEvenThread(arr, size);
    if (!answer) {
        free(arr);
        return 0;
    }
    printf("Answer with thread even: %ld\n", *answer);
    free(answer);
    clock_t finish = clock();
    clock_t total = finish - start;
    printf("Total thread time: %lu\n", total);

    start = clock();
    answer=sumEven(arr, size);
    if (!answer) {
        free(arr);
        return 0;
    }
    printf("Answer without thread even: %ld\n", *answer);
    free(answer);
    answer=sumNotEven(arr, size);
    if (!answer) {
        free(arr);
        return 0;
    }
    printf("Answer not even: %ld\n", *answer);
    free(answer);
    finish = clock();
    total = finish - start;
    printf("Total non thread time: %lu\n", total);
    free(arr);
    return 0;
}
