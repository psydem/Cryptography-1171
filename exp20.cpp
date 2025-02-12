#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8  // 64-bit block size

// XOR-based encryption (simulating 3DES)
void simple_encrypt(const char *plaintext, const char *key, char *ciphertext) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i % BLOCK_SIZE];
    }
}

// XOR-based decryption (same as encryption for XOR method)
void simple_decrypt(const char *ciphertext, const char *key, char *plaintext) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ key[i % BLOCK_SIZE];
    }
}

// Introduce an error in a specific ciphertext block
void introduce_error(char *ciphertext, int block_num) {
    ciphertext[block_num * BLOCK_SIZE] ^= 0xFF;  // Flip a bit in the block
}

int main() {
    // ? Fix: Use exactly 8 characters (excluding '\0')
    char plaintext[2][BLOCK_SIZE + 1] = {"Block_1A", "Block_2B"};
    char ciphertext_ecb[2][BLOCK_SIZE], ciphertext_cbc[2][BLOCK_SIZE];
    char decrypted_ecb[2][BLOCK_SIZE + 1], decrypted_cbc[2][BLOCK_SIZE + 1];

    // ? Fix: Reduce key and IV size to exactly 8 bytes
    char key[BLOCK_SIZE + 1] = "Secret_1";
    char iv[BLOCK_SIZE + 1] = "InitVect";  // Corrected length

    printf("Original Plaintext:\n");
    for (int i = 0; i < 2; i++) {
        printf("P%d: %s\n", i + 1, plaintext[i]);
    }

    // **Encrypt using ECB Mode**
    for (int i = 0; i < 2; i++) {
        simple_encrypt(plaintext[i], key, ciphertext_ecb[i]);
    }

    // **Encrypt using CBC Mode**
    char prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE); // Start with IV
    for (int i = 0; i < 2; i++) {
        char temp_block[BLOCK_SIZE];
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp_block[j] = plaintext[i][j] ^ prev_block[j]; // XOR with previous block
        }
        simple_encrypt(temp_block, key, ciphertext_cbc[i]);
        memcpy(prev_block, ciphertext_cbc[i], BLOCK_SIZE);
    }

    // **Introduce an error in the first ciphertext block**
    introduce_error((char *)ciphertext_ecb, 0);
    introduce_error((char *)ciphertext_cbc, 0);

    // **Decrypt ECB Mode**
    for (int i = 0; i < 2; i++) {
        simple_decrypt(ciphertext_ecb[i], key, decrypted_ecb[i]);
        decrypted_ecb[i][BLOCK_SIZE] = '\0'; // ? Fix: Null-terminate
    }

    // **Decrypt CBC Mode**
    memcpy(prev_block, iv, BLOCK_SIZE); // Reset IV
    for (int i = 0; i < 2; i++) {
        char temp_block[BLOCK_SIZE];
        simple_decrypt(ciphertext_cbc[i], key, temp_block);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            decrypted_cbc[i][j] = temp_block[j] ^ prev_block[j];
        }
        memcpy(prev_block, ciphertext_cbc[i], BLOCK_SIZE);
        decrypted_cbc[i][BLOCK_SIZE] = '\0'; // ? Fix: Null-terminate
    }

    printf("\nDecrypted ECB Mode (Error in C1 affects only P1):\n");
    for (int i = 0; i < 2; i++) {
        printf("P%d: %s\n", i + 1, decrypted_ecb[i]);
    }

    printf("\nDecrypted CBC Mode (Error in C1 affects P1 & P2):\n");
    for (int i = 0; i < 2; i++) {
        printf("P%d: %s\n", i + 1, decrypted_cbc[i]);
    }

    return 0;
}

