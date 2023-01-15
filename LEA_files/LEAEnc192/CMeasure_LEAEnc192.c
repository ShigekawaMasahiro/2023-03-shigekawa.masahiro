#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "LEAEnc192.h"

void LEA_En_192(const unsigned int Plain[4], unsigned int Cipher[4],const unsigned int Key_K[6]);

int main(int argc, char *argv[]) {
  const unsigned int Key_K[] = {0x3c2d1e0f, 0x78695a4b, 0xb4a59687, 0xf0e1d2c3, 0xc3d2e1f0, 0x8796a5b4};
  const unsigned int Plain[] = {0x23222120, 0x27262524, 0x2b2a2928, 0x2f2e2d2c};
  const unsigned int Cipher_Ans[] = {0x325eb96f, 0x871bad5a,0x35f5dc8c,0xf2c67476};

  // Check the result.
    unsigned int Cipher[4] = {0};
    LEA_En_192(Plain, Cipher, Key_K);
  if (memcmp(Cipher_Ans, Cipher, sizeof(Cipher_Ans)) == 0) {
    printf("OK\n");
  } else {
    printf("NG\n");
    for (int32_t i = 0; i < 4; ++i) {
      printf("%d  %08x %08x\n", i, Cipher_Ans[i], Cipher[i]);
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
      LEA_En_192(Plain, Cipher, Key_K);
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