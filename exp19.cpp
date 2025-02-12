#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8  // Block size for 3DES (64 bits)

// Example 3DES encryption function (simple XOR-based for illustration)
void simple_3des_encrypt(const char *plaintext, const char *key, char *ciphertext) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = plaintext[i] ^ key[i % 24]; // 24-byte key for 3DES
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext
}

// Example 3DES decryption function (same as encryption for XOR-based method)
void simple_3des_decrypt(const char *ciphertext, const char *key, char *plaintext) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        plaintext[i] = ciphertext[i] ^ key[i % 24];
    }
    plaintext[i] = '\0'; // Null-terminate the plaintext
}

int main() {
    char plaintext[] = "Encrypt this text!";
    char key[25] ="1234567890abcdef12345678"; // 24-byte key for 3DES
    char ciphertext[100];
    char decrypted_text[100];

    // Encrypt
    simple_3des_encrypt(plaintext, key, ciphertext);
    printf("Ciphertext (Hex): ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Decrypt
    simple_3des_decrypt(ciphertext, key, decrypted_text);
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}

