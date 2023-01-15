#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "LEADec128.h"

void LEA_De_128(unsigned int Plain[4], const unsigned int Cipher[4], const unsigned int Key_K[4]);

int main(int argc, char *argv[]) {
  const unsigned int Key_K[] = {0x3c2d1e0f, 0x78695a4b, 0xb4a59687, 0xf0e1d2c3};
  const unsigned int Cipher[] = {0x354ec89f, 0x18c6c628, 0xa7c73255, 0xfd8b6404};
  const unsigned int Plain_Ans[] = {0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};

  // Check the result.
    unsigned int Plain[4] = {0};
    LEA_De_128(Plain, Cipher, Key_K);
  if (memcmp(Plain_Ans, Plain, sizeof(Plain_Ans)) == 0) {
    printf("OK\n");
  } else {
    printf("NG\n");
    for (int32_t i = 0; i < 4; ++i) {
      printf("%d  %08x %08x\n", i, Plain_Ans[i], Plain[i]);
    }
    exit(EXIT_FAILURE);
  }

  // Measure execution time.
  // This value is the same as the Python script.
  const int32_t NUM_OF_LOOPS = 1 << 17;
  struct timeval start;
  struct timeval end;
  gettimeofday(&start, NULL);
  for (volatile int32_t i = 0; i < NUM_OF_LOOPS; ++i) {
      LEA_De_128(Plain, Cipher, Key_K);
  }
  gettimeofday(&end, NULL);
  const double elapsed_time_us = 1000000.0 * (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec);
  const double elapsed_time_ns = elapsed_time_us * 1000.0;
  printf("NUM: %d\n", NUM_OF_LOOPS);
  printf("Total: %lf us = %lf ns\n", elapsed_time_us, elapsed_time_ns);
  printf("Per 1 time\n");
  printf("Total: %lf us = %lf ns\n", elapsed_time_us / NUM_OF_LOOPS, elapsed_time_ns / NUM_OF_LOOPS);

  return 0;

}