#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to compute GCD (Greatest Common Divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to encrypt using Affine Cipher
void affineEncrypt(char *plaintext, int a, int b) {
    if (gcd(a, 26) != 1) { // Check if 'a' is coprime with 26
        printf("Error: 'a' must be coprime with 26.\n");
        return;
    }

    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int p = plaintext[i] - base; // Convert letter to 0-based index
            int c = (a * p + b) % 26;   // Apply affine cipher formula
            plaintext[i] = base + c;   // Convert back to character
        }
    }
}

// Main function
int main() {
    char plaintext[100];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    printf("Enter the value of a: ");
    scanf("%d", &a);

    printf("Enter the value of b: ");
    scanf("%d", &b);

    affineEncrypt(plaintext, a, b);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}

