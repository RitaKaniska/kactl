/**
 * Author: DeMen100ns
 * Date: 2024-01-01
 * License: CC0
 * Source: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
 * Description: Cheat sheet of SSE/AVX intrinsics, for doing arithmetic on several numbers at once.
 * Can provide a constant factor improvement of about 4, orthogonal to loop unrolling.
 * Operations follow the pattern \texttt{"\_mm(256)?\_name\_(si(128|256)|epi(8|16|32|64)|pd|ps)"}. Not all are described here;
 * grep for \texttt{\_mm\_} in \texttt{/usr/lib/gcc/{*}/4.9/include/} for more.
 * If AVX is unsupported, try 128-bit operations, "emmintrin.h" and \#define \texttt{\_\_SSE\_\_} and \texttt{\_\_MMX\_\_} before including it.
 * For aligned memory use \texttt{\_mm\_malloc(size, 32)} or \texttt{int buf[N] alignas(32)}, but prefer loadu/storeu.
 */

#include <immintrin.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

void example(){
    __m256i zero = _mm256_setzero_si256(); // set everything to 0
    __m256i eight = _mm256_set1_epi32(8); // set the vector of 8 integers to be equal to 8
    __m256i three = _mm256_set1_epi32(3);
    
    __m256i pi = _mm256_setr_epi32(3, 1, 4, 1, 5, 9, 2, 6); // NOTE: set and setr are opposites of each other
    // mm_setr_epi32(3, 1, 4, 1, 5, 9, 2, 6) -> first value == 3, second value == 1, third value == 4, forth value == 1, ...
    // mm_set_epi32(3, 1, 4, 1, 5, 9, 2, 6) -> first value == 6, second value == 2, third value == 9, forth value == 5, ...

    int arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    __m256i a0 = _mm256_loadu_si256((__m256i*) &arr[0]); // [0, 1, 2, 3, 4, 5, 6, 7]
    __m256i a4 = _mm256_loadu_si256((__m256i*) &arr[8]); // [8, 9, 10, 11, 12, 13, 14, 15]

    // _mm_insert_epi32(a, i, j) changes j-th number of a to value i
    a0 = _mm256_insert_epi32(a0, 99, 1); // [0, 99, 2, 3, 4, 5, 6, 7]

    //also can use bitwise operator and/or/xor/notand
    __m256i sm = _mm256_add_epi32(a0, a4); // [8, 108, 12, 14, 16, 18, 20, 22] (sum i-th element of a0 with i-th element of a4)
    __m256i mx = _mm256_max_epi32(pi, a0); // [3, 99, 4, 3, 5, 9, 6, 7] (maximum of the i-th element of pi and i-th element of a0)
    __m256i sb = _mm256_sub_epi32(a4, a0); // [8, -90, 8, 8, 8, 8, 8, 8] (subtract i-th element of a0 from i-th element of pi)

    __m256i mul = _mm256_mullo_epi32(sm, mx); // [24, 10692, 48, 42, 80, 162, 120, 154] (multiply i-th element of sm with mx)
    
    // _mm_cmpgt_epi32(a, b) returns mask containing a greater than b
    // note that 2^32-1 = -1 (all 32 bit is set)
    __m256i mskg = _mm256_cmpgt_epi32(pi, three); // contains [0, 0, 2^32-1, 0, 2^32-1, 2^32-1, 0, 2^32-1]
    // _mm_cmpeq_epi32(a, b) returns mask containing a equal to b
    __m256i mske = _mm256_cmpeq_epi32(pi, three); // contains [2^32-1, 0, 0, 0, 0, 0, 0, 0]

    // _mm256_blendv_epi8 (a, b, mask) //if mask[i] = 0 -> ans[i] = a[i], else ans[i] = b[i]
    __m256i mix = _mm256_blendv_epi8(eight, pi, mskg); // contains [8, 8, 4, 8, 5, 9, 8, 6] (more details below)

    //_mm256_permutevar8x32_epi32(a, msk) //reorder value of a to msk order.
    // sm = [8, 108, 12, 14, 16, 18, 20, 22]
    __m256i mask = _mm256_setr_epi32(3, 4, 5, 6, 7, 2, 1, 0);
    __m256i newsm = _mm256_permutevar8x32_epi32(sm, mask); //[14, 16, 18, 20, 22, 12, 108, 8]
    
    int mxarr[8]; 
    _mm256_storeu_si256((__m256i*) mxarr, mx); // stores values of mx into mxarr

    int sm0 = _mm256_extract_epi32(sm, 2); // extract the 2-nd element of sum (= 18)
}
