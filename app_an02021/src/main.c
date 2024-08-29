#include <stdio.h>
#include <xcore/hwtimer.h>
#include "memcpy_ext.h"

#define BLOCKS 512

// external array declaration begin
__attribute__((section(".ExtMem_data")))
unsigned int array_ext[MEMCPY_EXT_BLOCK_BYTES / sizeof(int) * BLOCKS] = {1,5,20};
// external array declaration end

unsigned int array_int[MEMCPY_EXT_BLOCK_BYTES / sizeof(int) * BLOCKS];
  
// external function declaration begin
__attribute__((section(".ExtMem_code")))
unsigned int add_six(unsigned int a) {
    return a + 6;
}
// external function declaration end

void use_lpddr(void) {
    for (int i = 0; i < 3; i++) {
        printf("Result: %d\n", add_six(array_ext[i]));
    }
}

int main(void) {
    int bytes = BLOCKS * MEMCPY_EXT_BLOCK_BYTES;
    use_lpddr();
    int t0 = get_reference_time();
    memcpy_ext(array_int, array_ext, BLOCKS);
    int t1 = get_reference_time();
    float seconds1 = (t1 - t0) * 10e-9;
    printf("%d bytes copied in %5.3f us %4.0f MByte/sec\n",
           bytes,
           seconds1 * 1e6,
           bytes / (1024 * 1024.0) / seconds1);
    t0 = get_reference_time();
    memcpy_ext(array_int, array_ext, BLOCKS);
    t1 = get_reference_time();
    seconds1 = (t1 - t0) * 10e-9;
    printf("%d bytes copied in %5.3f us %4.0f MByte/sec\n",
           bytes,
           seconds1 * 1e6,
           bytes / (1024 * 1024.0) / seconds1);
}
