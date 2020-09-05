#include "IZ2_STATIC.h"
#include <stdlib.h>

static int64_t *getAnswer(const int64_t *arr, size_t size, int64_t *answer, int8_t evenFlag);

int64_t *sumEven(const int64_t *arr, size_t size) {
    int64_t *answer=(int64_t *)malloc(sizeof(int64_t));
    if(!answer)
        return NULL;
    if (arr == NULL){
        free(answer);
        return NULL;
    }

    return getAnswer(arr, size, answer, 1);
}

int64_t *sumNotEven(const int64_t *arr, size_t size) {
    int64_t *answer=(int64_t *)malloc(sizeof(int64_t));
    if(!answer)
        return NULL;
    if (arr == NULL){
        free(answer);
        return NULL;
    }
    return getAnswer(arr, size, answer, 0);
}

int64_t *getAnswer(const int64_t *arr, size_t size, int64_t *answer, int8_t evenFlag){
    *(answer)=0;
    if(evenFlag){
        for (size_t i = 0; i < size; ++i) {
            if ((arr[i] % 2) == 0)
                *(answer) += arr[i];
        }
        return answer;
    }
    for (size_t i = 1; i < size; ++i) {
        if ((arr[i] % 2) != 0)
            *(answer) += arr[i];
    }
    return answer;
}
