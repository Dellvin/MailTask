//
// Created by Dellvin on 06.03.2020.
//
#include "gtest/gtest.h"

extern "C" {
#include "libIZ2_dymamic.h"
#include "IZ2_STATIC.h"
}



TEST(test, Test2) {

    int64_t *arr;
    size_t size = 10000;
    arr = (int64_t *) malloc(size * sizeof(int64_t));
    if (!arr) return;
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }

    int64_t *answer1=nullptr;
    int64_t *answer2=nullptr;
    int64_t *answer3=nullptr;
    int64_t *answer4=nullptr;
    clock_t start;
    start = clock();
   answer1=sumNotEvenThread(arr, size);
    if (!answer1) {
        free(arr);
        return;
    }
    EXPECT_EQ(*answer1, 25000000);
    printf("Answer with thread NOT even: %ld\n", *answer1);
    answer2=sumEvenThread(arr, size);
    if (!answer2) {
        free(answer1);
        free(arr);
        return;
    }
    EXPECT_EQ(*answer2, 24995000);
    printf("Answer with thread even: %ld\n", *answer2);
    clock_t finish = clock();
    clock_t total = finish - start;
    printf("Total thread time: %lu\n", total);

    start = clock();
    answer3 = sumEven(arr, size);
    if(!answer3){
        free(answer1);
        free(answer2);
        free(arr);
        return;
    }
    printf("Answer without thread even: %ld\n", *answer3);
    EXPECT_EQ(*answer2, *answer3);
    answer4 = sumNotEven(arr, size);

    if(!answer4){
        free(answer1);
        free(answer2);
        free(answer3);
        free(arr);
        return;
    }

    printf("Answer not even: %ld\n", *answer4);
    EXPECT_EQ(*answer1, *answer4);
    finish = clock();
    total = finish - start;
    printf("Total non thread time: %lu\n", total);



    free(answer1);
    free(answer2);
    free(answer3);
    free(answer4);
    free(arr);
}
