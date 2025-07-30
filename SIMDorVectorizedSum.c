// File: src/simd_sum.c
#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>

float simd_vector_sum(const float* arr, size_t len) {
    __m256 vsum = _mm256_setzero_ps();
    size_t i = 0;
    for (; i + 7 < len; i += 8) {
        __m256 v = _mm256_loadu_ps(arr + i);
        vsum = _mm256_add_ps(vsum, v);
    }
    float temp[8];
    _mm256_storeu_ps(temp, vsum);
    float sum = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7];
    for (; i < len; ++i) sum += arr[i];
    return sum;
}

int main(void) {
    float arr[16];
    for (int i = 0; i < 16; ++i) arr[i] = 1.0f * (i + 1);
    printf("SIMD Sum: %.1f\n", simd_vector_sum(arr, 16));
    return 0;
}
