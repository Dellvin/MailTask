#pragma once
#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdint.h>

int64_t *sumEvenThread(int64_t *arr, size_t size);
int64_t *sumNotEvenThread(int64_t *arr, size_t size);
