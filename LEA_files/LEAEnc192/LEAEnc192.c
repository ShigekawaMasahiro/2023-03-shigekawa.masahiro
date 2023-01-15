#include <stdint.h>
#include <string.h>
#define Nr 28 //The number of rounds for the LEA algorithm
#define ROL(a, s) (((a) << (s)) | ((a) >> (32 - (s))))
#define ROR(a, s) (((a) >> (s)) | ((a) << (32 - (s))))


void LEA_En_192(const unsigned int Plain[4], unsigned int Cipher[4], const unsigned int Key_K[6]) {
	static const unsigned int Delta[8] = {0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957}; //Constant values
    static unsigned int T[6] = {0};
    static unsigned int X[4] = {0};
    unsigned int K0[Nr] = {}, K1[Nr] = {}, K2[Nr] = {}, K3[Nr] = {}, K4[Nr] = {}, K5[Nr] = {};
    static unsigned int X_Next[4] = {0};
    int32_t i;

    memcpy(T, Key_K, sizeof(T));
    memcpy(X, Plain, sizeof(X));
    for (i = 0; i < Nr; i++){
        T[0] = ROL(T[0] + ROL(Delta[i % 6], i + 0), 1);
        T[1] = ROL(T[1] + ROL(Delta[i % 6], i + 1), 3);
        T[2] = ROL(T[2] + ROL(Delta[i % 6], i + 2), 6);
        T[3] = ROL(T[3] + ROL(Delta[i % 6], i + 3), 11);
        T[4] = ROL(T[4] + ROL(Delta[i % 6], i + 4), 13);
        T[5] = ROL(T[5] + ROL(Delta[i % 6], i + 5), 17);
        K0[i] = T[0]; K1[i] = T[1]; K2[i] = T[2]; K3[i] = T[3]; K4[i] = T[4]; K5[i] = T[5];
    }
    for (i = 0; i < Nr; i++){
    	X_Next[0] = ROL((X[0] ^ K0[i]) + (X[1] ^ K1[i]), 9);
    	X_Next[1] = ROR((X[1] ^ K2[i]) + (X[2] ^ K3[i]), 5);
    	X_Next[2] = ROR((X[2] ^ K4[i]) + (X[3] ^ K5[i]), 3);
    	X_Next[3] = X[0];
    	memcpy(X, X_Next, sizeof(X));
    }
    memcpy(Cipher, X, sizeof(X));
}
