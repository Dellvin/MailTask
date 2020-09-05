#include "libIZ2_dymamic.h"

#include <errno.h>

#include <time.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <stddef.h>

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

enum typeSum {
    EVEN,
    NOT_EVEN
};

typedef struct threadParams {
    int64_t *arr;
    enum typeSum type;
    size_t begin;
    size_t end;
    int64_t sum;
    size_t size;
} threadParams;


static void *sumPart(void *args);

static void setStruct(threadParams *obj, int64_t *arr, enum typeSum type, size_t begin, size_t end, int64_t sum, size_t size);

static int setThread(threadParams *data, pthread_t *threads, uint16_t currentThread);

static void getAnswer(int64_t *answer, threadParams *arr, uint16_t threadCount);

static void deleter(threadParams **arr, int64_t **answer, pthread_t **threads);

int64_t *sumEvenThread(int64_t *arr, size_t size) {
    int64_t *answer = (int64_t*)malloc(sizeof(int64_t));
    uint16_t threadCount=8;
    if(!answer){
        return NULL;
    }
    if (arr == NULL){
        deleter(NULL, &answer, NULL);
        return NULL;
    }

    threadParams *data = (threadParams *) malloc(threadCount * sizeof(threadParams));
    if (!data){
        deleter(NULL, &answer, NULL);
        return NULL;
    }
    pthread_t *threads = (pthread_t *) malloc(threadCount * sizeof(pthread_t));
    for (uint16_t i = 0; i < threadCount; i++) {
        setStruct(&data[i], arr, EVEN, (size_t) ((size / threadCount) * i),
                  (size_t) (((size / threadCount) * (i + 1)) - 1), 0, size);
        if(setThread(data, threads, i)==-1){
            deleter(&data, &answer, &threads);
            return NULL;
        }
    }
    for (uint16_t i = 0; i < threadCount; i++){
        int stat = pthread_join(threads[i], NULL);
        if(stat){
            handle_error_en(stat, "pthread_join");
            deleter(&data, &answer, &threads);
            return NULL;
        }
    }
    getAnswer(answer, &data[0], threadCount);
    deleter(&data, NULL, &threads);
    return answer;
}


int64_t *sumNotEvenThread(int64_t *arr, size_t size) {
    int64_t *answer=(int64_t*)malloc(sizeof(int64_t));
    if(!answer)
        return NULL;
    uint16_t threadCount=8;
    if (arr == NULL){
        deleter(NULL, &answer, NULL);
        return NULL;
    }
    threadParams *data = (threadParams*) malloc(threadCount * sizeof(threadParams));
    if (!data){
        deleter(NULL, &answer, NULL);
        return NULL;
    }
    pthread_t *threads = (pthread_t *) malloc(threadCount * sizeof(pthread_t));
    if (!threads) {
        deleter(&data, &answer, NULL);
        return NULL;
    }
    for (uint16_t i = 0; i < threadCount; i++) {
        size_t end=(size_t) ((size / threadCount) * (i + 1));
        if ((i + 1) == threadCount) end += 1;
        setStruct(&data[i], arr, NOT_EVEN, (size_t) ((size / threadCount) * i),
                  end, 0, size);
        if(setThread(data, threads, i)==-1){
            deleter(&data, &answer, &threads);
            return NULL;
        }
    }
    for (uint16_t i = 0; i < threadCount; i++){
        int stat=pthread_join(threads[i], NULL);
        if(stat){
            handle_error_en(stat, "pthread_join");
            deleter(&data, &answer, &threads);
            return NULL;
        }
    }
    getAnswer(answer, &data[0], threadCount);
    deleter(&data, NULL, &threads);
    return answer;
}


static void *sumPart(void *args) {
    threadParams *data = (threadParams *) args;
    if (data->type == EVEN) {
        for (uint64_t i = data->begin; i < data->end; ++i) {
            if ((data->arr[i] % 2) == 0) {
                data->sum += data->arr[i];
            }
        }
        return NULL;
    }

    for (uint64_t j = data->begin; j < data->end; ++j) {
        if(j<data->size){
            if ((data->arr[j] % 2)) {
                data->sum += data->arr[j];
            }
        }
    }
    return NULL;
}


static void setStruct(threadParams *obj, int64_t *arr, enum typeSum type, size_t begin, size_t end, int64_t sum, size_t size){
    obj->arr=arr;
    obj->type=type;
    obj->begin=begin;
    obj->end=end;
    obj->sum=sum;
    obj->size=size;
}

static void getAnswer(int64_t *answer, threadParams *arr, uint16_t threadCount){
    *(answer) = 0;
    for (uint16_t i = 0; i < threadCount; i++) {
        *(answer) += (arr+i)->sum;
    }
}

static void deleter(threadParams **arr, int64_t **answer, pthread_t **threads){
    if(arr) free(*arr);
    if(answer) free(*answer);
    if(threads) free(*threads);
}

int setThread(threadParams *data, pthread_t *threads, uint16_t currentThread){
    int status=pthread_create(&(threads[currentThread]), NULL, sumPart, &data[currentThread]);
    if(status){
        handle_error_en(status, "pthread_create");
        return -1;
    }
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(currentThread, &cpuset);
    pthread_setaffinity_np(threads[currentThread], sizeof(cpu_set_t), &cpuset);
    return 0;
}
