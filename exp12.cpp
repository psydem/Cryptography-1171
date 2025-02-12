#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform matrix multiplication and encryption
void encrypt(int key[2][2], int plaintext[], int ciphertext[], int length) {
    for (int i = 0; i < length; i += 2) {
        ciphertext[i] = (key[0][0] * plaintext[i] + key[0][1] * plaintext[i + 1]) % 26;
        ciphertext[i + 1] = (key[1][0] * plaintext[i] + key[1][1] * plaintext[i + 1]) % 26;
    }
}

// Function to convert characters to numerical representation
void textToNumbers(char text[], int numbers[], int length) {
    for (int i = 0; i < length; i++) {
        numbers[i] = toupper(text[i]) - 'A';
    }
}

// Function to convert numbers back to text
void numbersToText(int numbers[], char text[], int length) {
    for (int i = 0; i < length; i++) {
        text[i] = numbers[i] + 'A';
    }
    text[length] = '\0';
}

int main() {
    char plaintext[] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";
    int length = strlen(plaintext);

    // Ensure even length by padding with 'X'
    if (length % 2 != 0) {
        plaintext[length] = 'X';
        length++;
    }

    int key[2][2] = {{9, 4}, {5, 7}};
    int plaintextNumbers[length], ciphertextNumbers[length];
    char ciphertext[length + 1];

    // Convert text to numbers
    textToNumbers(plaintext, plaintextNumbers, length);

    // Encrypt using Hill cipher
    encrypt(key, plaintextNumbers, ciphertextNumbers, length);

    // Convert numbers back to text
    numbersToText(ciphertextNumbers, ciphertext, length);

    printf("Encrypted Text: %s\n", ciphertext);

    return 0;
}

