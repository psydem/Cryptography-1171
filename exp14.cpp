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

// Function to encrypt the plaintext using the key stream
void encrypt(char plaintext[], int key[], int keyLength) {
    int len = strlen(plaintext);
    char ciphertext[len + 1];

    printf("Ciphertext: ");
    for (int i = 0; i < len; i++) {
        if (plaintext[i] == ' ') { 
            printf(" "); // Preserve spaces
            continue;
        }
        int p = charToNum(plaintext[i]);
        int c = (p + key[i % keyLength]) % MOD;
        ciphertext[i] = numToChar(c);
        printf("%c", ciphertext[i]);
    }
    ciphertext[len] = '\0';
    printf("\n");
}

// Function to decrypt the ciphertext using the key stream
void decrypt(char ciphertext[], int key[], int keyLength) {
    int len = strlen(ciphertext);
    char plaintext[len + 1];

    printf("Decrypted Text: ");
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] == ' ') { 
            printf(" "); // Preserve spaces
            continue;
        }
        int c = charToNum(ciphertext[i]);
        int p = (c - key[i % keyLength] + MOD) % MOD;
        plaintext[i] = numToChar(p);
        printf("%c", plaintext[i]);
    }
    plaintext[len] = '\0';
    printf("\n");
}

// Function to calculate the key that decrypts the given ciphertext to a new plaintext
void findNewKey(char ciphertext[], char newPlaintext[], int newKey[]) {
    int len = strlen(ciphertext);
    
    printf("New Key: ");
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] == ' ' || newPlaintext[i] == ' ') {
            printf("  "); // Preserve spaces
            continue;
        }
        int c = charToNum(ciphertext[i]);
        int p = charToNum(newPlaintext[i]);
        newKey[i] = (p - c + MOD) % MOD;
        printf("%d ", newKey[i]);
    }
    printf("\n");
}

int main() {
    // Given plaintext
    char plaintext[] = "SEND MORE MONEY";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}; // Given key stream
    int keyLength = sizeof(key) / sizeof(key[0]);

    printf("Encrypting plaintext: %s\n", plaintext);
    encrypt(plaintext, key, keyLength);

    // Given new plaintext for decryption
    char newPlaintext[] = "CASH NOT NEEDED";
    int newKey[strlen(newPlaintext)];

    // Find the new key that decrypts the ciphertext to "CASH NOT NEEDED"
    findNewKey("VFPW NVHV CJYLLD", newPlaintext, newKey);

    return 0;
}

