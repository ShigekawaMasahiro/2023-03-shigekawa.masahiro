#include <stdint.h>
#include <string.h>
#define Nr 24 //The number of rounds for the LEA algorithm
#define ROL(a, s) (((a) << (s)) | ((a) >> (32 - (s))))
#define ROR(a, s) (((a) >> (s)) | ((a) << (32 - (s))))

void Generate_Key_T(unsigned int *, int32_t i, const unsigned int *);
void TtoK(unsigned int *, unsigned int *);
void Update(unsigned int *, unsigned int *, unsigned int *);

void LEA_En_128(const unsigned int Plain[4], unsigned int Cipher[4], const unsigned int Key_K[4]) {
#pragma HLS INTERFACE s_axilite port=Key_K
#pragma HLS INTERFACE s_axilite port=Cipher
#pragma HLS INTERFACE s_axilite port=Plain
#pragma HLS INTERFACE s_axilite port=return
	static const unsigned int Delta[8] = {0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957}; //Constant values
    static unsigned int T[4] = {0};
    static unsigned int X[4] = {0};
    static unsigned int K[6] = {0};
    static unsigned int X_Next[4] = {0};

    memcpy(T, Key_K, sizeof(T));
    memcpy(X, Plain, sizeof(X));

    for (int32_t i = 0; i < Nr; i++) {
    	Generate_Key_T(T, i, Delta);
    	TtoK(T, K);
    	Update(X_Next, X, K);
    	memcpy(X, X_Next, sizeof(X));
    }
    memcpy(Cipher, X, sizeof(X));
}

void Generate_Key_T(unsigned int *T, int32_t i, const unsigned int * Delta){
#pragma HLS UNROLL
	T[0] = ROL(T[0] + ROL(Delta[i & 0x3], i + 0), 1);
	T[1] = ROL(T[1] + ROL(Delta[i & 0x3], i + 1), 3);
	T[2] = ROL(T[2] + ROL(Delta[i & 0x3], i + 2), 6);
	T[3] = ROL(T[3] + ROL(Delta[i & 0x3], i + 3), 11);
}
void TtoK(unsigned int *T, unsigned int *K){
#pragma HLS UNROLL
    K[0] = T[0];
    K[1] = T[1];
    K[2] = T[2];
    K[3] = T[1];
    K[4] = T[3];
    K[5] = T[1];
}
void Update(unsigned int *X_Next, unsigned int *X, unsigned int *K){
#pragma HLS UNROLL
	X_Next[0] = ROL((X[0] ^ K[0]) + (X[1] ^ K[1]), 9);
	X_Next[1] = ROR((X[1] ^ K[2]) + (X[2] ^ K[3]), 5);
	X_Next[2] = ROR((X[2] ^ K[4]) + (X[3] ^ K[5]), 3);
	X_Next[3] = X[0];
}
