#include <stdint.h>
#include <string.h>
#define Nr 24 //The number of rounds for the LEA algorithm
#define ROL(a, s) (((a) << (s)) | ((a) >> (32 - (s))))
#define ROR(a, s) (((a) >> (s)) | ((a) << (32 - (s))))

void LEA_De_128(unsigned int Plain[4], const unsigned int Cipher[4], const unsigned int Key_K[4]){
	unsigned int Delta[8] = {0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957}; //Constant values
	unsigned int T[4] = {};
	unsigned int K0[Nr] = {}, K1[Nr] = {}, K2[Nr] = {}, K3[Nr] = {}, K4[Nr] = {}, K5[Nr] = {};
	static unsigned int X[4] = {0};
	static unsigned int X_Next[4] = {0};
	int i;

	memcpy(T, Key_K, sizeof(T));

    for (i = 0; i < Nr; i++){
        T[0] = ROL(T[0] + ROL(Delta[i & 0x3], i + 0), 1);
        T[1] = ROL(T[1] + ROL(Delta[i & 0x3], i + 1), 3);
        T[2] = ROL(T[2] + ROL(Delta[i & 0x3], i + 2), 6);
        T[3] = ROL(T[3] + ROL(Delta[i & 0x3], i + 3), 11);
        K0[i] = T[0]; K1[i] = T[1]; K2[i] = T[2]; K3[i] = T[1]; K4[i] = T[3]; K5[i] = T[1];
    }

    memcpy(X_Next, Cipher, sizeof(X_Next));

    for (i = Nr - 1; i >= 0; i--){
        X[0] = X_Next[3];
        X[1] = (ROR(X_Next[0], 9) - (X[0] ^ K0[i])) ^ K1[i];
        X[2] = (ROL(X_Next[1], 5) - (X[1] ^ K2[i])) ^ K3[i];
        X[3] = (ROL(X_Next[2], 3) - (X[2] ^ K4[i])) ^ K5[i];
        memcpy(X_Next, X, sizeof(X_Next));
    }
    memcpy(Plain, X, sizeof(X));
}
