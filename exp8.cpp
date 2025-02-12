#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to remove duplicate characters from the keyword
void removeDuplicates(char *str) {
    int len = strlen(str);
    int index = 0;

    for (int i = 0; i < len; i++) {
        int j;
        for (j = 0; j < i; j++) {
            if (str[i] == str[j]) {
                break;
            }
        }
        if (j == i) {
            str[index++] = str[i];
        }
    }
    str[index] = '\0';
}

// Function to generate the cipher alphabet
void generateCipherAlphabet(char *keyword, char *cipher) {
    int used[26] = {0}; // Array to mark used characters
    int index = 0;

    // Add keyword to the cipher alphabet
    for (int i = 0; keyword[i] != '\0'; i++) {
        if (!used[keyword[i] - 'A']) {
            cipher[index++] = keyword[i];
            used[keyword[i] - 'A'] = 1;
        }
    }

    // Add remaining letters of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }
    cipher[index] = '\0';
}

// Function to encrypt the plaintext
void encrypt(char *plaintext, char *cipher, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                ciphertext[i] = cipher[plaintext[i] - 'A'];
            } else {
                ciphertext[i] = tolower(cipher[plaintext[i] - 'a']);
            }
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Main function
int main() {
    char keyword[100], plaintext[100], ciphertext[100];
    char cipher[27];

    printf("Enter the keyword: ");
    scanf("%s", keyword);

    // Convert the keyword to uppercase
    for (int i = 0; keyword[i] != '\0'; i++) {
        keyword[i] = toupper(keyword[i]);
    }

    // Remove duplicates from the keyword
    removeDuplicates(keyword);

    // Generate the cipher alphabet
    generateCipherAlphabet(keyword, cipher);

    // Display the cipher alphabet
    printf("Cipher alphabet: %s\n", cipher);

    // Get the plaintext input
    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext); // Accept input with spaces

    // Encrypt the plaintext
    encrypt(plaintext, cipher, ciphertext);

    // Display the ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

