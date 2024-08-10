#include "utils.h"
#include <math.h>

float *normalize(float *arr, int size) {
    float denominator = sqrt(pow(arr[0], 2) + pow(arr[1], 2) + pow(arr[2], 2));

    for (int i = 0; i < size; i++) {
        arr[i] = arr[i] / denominator;
    }

    return arr;
}

float dotProduct(float *a, float *b) {
    float result = 0;

    for (int i = 0; i < 3; i++) {
        result += a[i] * b[i];
    }

    return result;
}

void reflect(float *direction, float *normal, float *reflected) {
    float dot = dotProduct(direction, normal);

    for (int i = 0; i < 3; i++) {
        reflected[i] = direction[i] - 2.0 * dot * normal[i];
    }
}