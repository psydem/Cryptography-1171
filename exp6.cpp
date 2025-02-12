#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to compute modular multiplicative inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No inverse exists
}

// Function to decrypt the affine cipher
void affineDecrypt(char *ciphertext, int a, int b) {
    int a_inv = modInverse(a, 26); // Compute modular inverse of 'a' under mod 26
    if (a_inv == -1) {
        printf("Error: 'a' has no modular inverse under mod 26.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) { // Check if the character is a letter
            char base = isupper(ciphertext[i]) ? 'A' : 'a'; // Determine case
            int C = ciphertext[i] - base; // Convert to 0-based index
            int P = (a_inv * (C - b + 26)) % 26; // Decrypt formula
            ciphertext[i] = base + P; // Convert back to character
        }
    }
}

int main() {
    char ciphertext[100];
    int a, b;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    // Known values for the problem
    a = 15; // Derived from congruences
    b = 1;  // Derived from congruences

    affineDecrypt(ciphertext, a, b);

    printf("Decrypted text: %s\n", ciphertext);

    return 0;
}

