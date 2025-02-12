#include <stdio.h>
#include <stdint.h>
#include <string.h>

// PC-1 Permutation Table (64-bit key to 56-bit)
int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};

// PC-2 Permutation Table (56-bit to 48-bit subkeys)
int PC2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

// Shift Schedule
int SHIFTS[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Subkeys Storage
uint64_t subkeys[16];

// Function to perform permutation
uint64_t permute(uint64_t input, int *table, int size, int inputSize) {
    uint64_t output = 0;
    for (int i = 0; i < size; i++) {
        output |= ((input >> (inputSize - table[i])) & 1) << (size - 1 - i);
    }
    return output;
}

// Left circular shift for 28-bit halves
uint32_t left_circular_shift(uint32_t value, int shift) {
    return ((value << shift) | (value >> (28 - shift))) & 0x0FFFFFFF;
}

// Generate 16 subkeys
void generate_subkeys(uint64_t key) {
    uint64_t permutedKey = permute(key, PC1, 56, 64);
    uint32_t C = (permutedKey >> 28) & 0x0FFFFFFF;  // First 28 bits
    uint32_t D = permutedKey & 0x0FFFFFFF;         // Second 28 bits

    for (int i = 0; i < 16; i++) {
        // Apply left circular shift
        C = left_circular_shift(C, SHIFTS[i]);
        D = left_circular_shift(D, SHIFTS[i]);

        // Combine C and D to form the 48-bit key (ensuring disjoint subsets)
        uint64_t combinedKey = ((uint64_t)C << 28) | D;

        // Apply PC-2 permutation to generate subkey
        subkeys[i] = permute(combinedKey, PC2, 48, 56);
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
    char keyHex[17];

    printf("Enter 16-character (64-bit) key in hex: ");
    scanf("%16s", keyHex);

    uint64_t key = hex_to_uint64(keyHex);

    generate_subkeys(key);

    printf("\nGenerated Subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("K%-2d: %012lX\n", i + 1, subkeys[i]);
    }

    return 0;
}

