#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

// Function to convert a character to numerical value (A=0, B=1, ..., Z=25)
int charToNum(char c) {
    return toupper(c) - 'A';
}

// Function to convert numerical value to a character
char numToChar(int num) {
    return num + 'A';
}

// Function to compute modular inverse of a number under MOD 26
int modInverse(int num, int mod) {
    num = num % mod;
    for (int x = 1; x < mod; x++) {
        if ((num * x) % mod == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

// Function to find the inverse of a 2x2 matrix modulo 26
void inverseMatrix(int key[2][2], int invKey[2][2]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
    if (det < 0) det += MOD; // Ensure positive determinant

    int detInverse = modInverse(det, MOD);
    if (detInverse == -1) {
        printf("Matrix is not invertible in mod 26.\n");
        exit(1);
    }

    // Compute adjugate matrix and multiply by determinant inverse mod 26
    invKey[0][0] = (key[1][1] * detInverse) % MOD;
    invKey[0][1] = (-key[0][1] * detInverse) % MOD;
    invKey[1][0] = (-key[1][0] * detInverse) % MOD;
    invKey[1][1] = (key[0][0] * detInverse) % MOD;

    // Ensure all values are positive modulo 26
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (invKey[i][j] < 0) invKey[i][j] += MOD;
        }
    }
}

// Hill cipher encryption function
void encrypt(int key[2][2], char plaintext[]) {
    int len = strlen(plaintext);
    
    // Remove spaces and convert to uppercase
    char cleanText[100];
    int cleanLen = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            cleanText[cleanLen++] = toupper(plaintext[i]);
        }
    }
    
    // Make the length even by padding with 'X' if needed
    if (cleanLen % 2 == 1) {
        cleanText[cleanLen++] = 'X';
    }
    
    printf("Ciphertext: ");
    for (int i = 0; i < cleanLen; i += 2) {
        int P1 = charToNum(cleanText[i]);
        int P2 = charToNum(cleanText[i + 1]);

        int C1 = (key[0][0] * P1 + key[0][1] * P2) % MOD;
        int C2 = (key[1][0] * P1 + key[1][1] * P2) % MOD;

        printf("%c%c", numToChar(C1), numToChar(C2));
    }
    printf("\n");
}

// Function to recover the encryption key from known plaintext-ciphertext pairs
void recoverKey(int plaintext[2][2], int ciphertext[2][2], int recoveredKey[2][2]) {
    int invPlaintext[2][2];

    // Compute the inverse of the plaintext matrix
    inverseMatrix(plaintext, invPlaintext);

    // Multiply ciphertext by the inverse of plaintext to recover the key
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            recoveredKey[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                recoveredKey[i][j] += ciphertext[i][k] * invPlaintext[k][j];
            }
            recoveredKey[i][j] %= MOD;
        }
    }
}

int main() {
    // Example key matrix
    int key[2][2] = {{9, 4}, {5, 7}};

    // Example plaintext (chosen for attack)
    char plaintext[] = "MEET";

    // Encrypt plaintext
    printf("Encrypting: %s\n", plaintext);
    encrypt(key, plaintext);

    // Known plaintext-ciphertext pairs (found from encryption)
    int plaintextMatrix[2][2] = {{12, 4}, {4, 19}}; // ME ET
    int ciphertextMatrix[2][2] = {{20, 10}, {2, 23}}; // UK CX (example)

    // Recover key
    int recoveredKey[2][2];
    recoverKey(plaintextMatrix, ciphertextMatrix, recoveredKey);

    // Print recovered key
    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", recoveredKey[i][j]);
        }
        printf("\n");
    }

    return 0;
}

