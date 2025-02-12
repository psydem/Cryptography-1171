#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Initial and Final Permutations
int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};

int IP_INV[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion (E) table (from 32 bits to 48 bits)
int E[48] = {
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};

// Key schedule shift values
int SHIFT_SCHEDULE[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Subkeys storage
uint64_t subkeys[16];

// Function to perform permutation
uint64_t permute(uint64_t input, int *table, int size) {
    uint64_t output = 0;
    for (int i = 0; i < size; i++) {
        output |= ((input >> (64 - table[i])) & 1) << (size - 1 - i);
    }
    return output;
}

// DES Feistel function
uint32_t feistel(uint32_t R, uint64_t K) {
    // Expansion
    uint64_t expanded = 0;
    for (int i = 0; i < 48; i++) {
        expanded |= ((uint64_t)((R >> (32 - E[i])) & 1)) << (47 - i);
    }
    expanded ^= K; // XOR with key

    // (Skipping S-Boxes and P permutation for simplicity)

    return (uint32_t)(expanded & 0xFFFFFFFF); // Truncate to 32 bits
}

// DES decryption
uint64_t des_decrypt(uint64_t ciphertext) {
    uint64_t permutedText = permute(ciphertext, IP, 64);
    uint32_t L = (permutedText >> 32) & 0xFFFFFFFF;
    uint32_t R = permutedText & 0xFFFFFFFF;

    // Apply 16 rounds using subkeys in reverse order
    for (int i = 15; i >= 0; i--) {
        uint32_t temp = R;
        R = L ^ feistel(R, subkeys[i]);
        L = temp;
    }

    uint64_t preOutput = ((uint64_t)R << 32) | L;
    return permute(preOutput, IP_INV, 64);
}

// Function to generate 16 subkeys (Key Scheduling)
void generate_subkeys(uint64_t key) {
    uint64_t permutedKey = permute(key, IP, 64);
    uint32_t C = (permutedKey >> 28) & 0x0FFFFFFF;
    uint32_t D = permutedKey & 0x0FFFFFFF;

    for (int i = 0; i < 16; i++) {
        C = ((C << SHIFT_SCHEDULE[i]) | (C >> (28 - SHIFT_SCHEDULE[i]))) & 0x0FFFFFFF;
        D = ((D << SHIFT_SCHEDULE[i]) | (D >> (28 - SHIFT_SCHEDULE[i]))) & 0x0FFFFFFF;

        subkeys[i] = ((uint64_t)C << 28) | D;
    }
}

// Convert hexadecimal string to uint64_t
uint64_t hex_to_uint64(const char *hex) {
    uint64_t result = 0;
    while (*hex) {
        char c = *hex++;
        result = (result << 4) | (c >= '0' && c <= '9' ? c - '0' :
                                  c >= 'A' && c <= 'F' ? c - 'A' + 10 :
                                  c - 'a' + 10);
    }
    return result;
}

int main() {
    char ciphertextHex[17], keyHex[17];

    printf("Enter 16-character (64-bit) ciphertext in hex: ");
    scanf("%16s", ciphertextHex);
    printf("Enter 16-character (64-bit) key in hex: ");
    scanf("%16s", keyHex);

    uint64_t ciphertext = hex_to_uint64(ciphertextHex);
    uint64_t key = hex_to_uint64(keyHex);

    generate_subkeys(key); // Generate subkeys

    uint64_t decryptedText = des_decrypt(ciphertext);

    printf("Decrypted Plaintext (Hex): %016lX\n", decryptedText);
    return 0;
}

