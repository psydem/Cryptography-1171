#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Playfair cipher matrix
char playfairMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

// Function to preprocess plaintext
void preprocessPlaintext(char *plaintext) {
    int len = strlen(plaintext);
    char temp[500];
    int j = 0;

    // Remove spaces, convert to uppercase, and handle 'J' -> 'I'
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            temp[j++] = toupper(plaintext[i] == 'J' ? 'I' : plaintext[i]);
        }
    }
    temp[j] = '\0';

    // Insert 'X' between duplicate letters in pairs
    char formatted[500];
    j = 0;
    for (int i = 0; temp[i]; i++) {
        formatted[j++] = temp[i];
        if (temp[i] == temp[i + 1]) {
            formatted[j++] = 'X';
        }
    }
    formatted[j] = '\0';

    // Ensure even length by adding 'X' if necessary
    if (strlen(formatted) % 2 != 0) {
        formatted[j++] = 'X';
        formatted[j] = '\0';
    }

    strcpy(plaintext, formatted);
}

// Function to find the position of a letter in the Playfair matrix
void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (playfairMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of characters
void encryptPair(char *a, char *b) {
    int row1, col1, row2, col2;

    findPosition(*a, &row1, &col1);
    findPosition(*b, &row2, &col2);

    if (row1 == row2) {
        // Same row: move right
        *a = playfairMatrix[row1][(col1 + 1) % SIZE];
        *b = playfairMatrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        // Same column: move down
        *a = playfairMatrix[(row1 + 1) % SIZE][col1];
        *b = playfairMatrix[(row2 + 1) % SIZE][col2];
    } else {
        // Rectangle: swap columns
        *a = playfairMatrix[row1][col2];
        *b = playfairMatrix[row2][col1];
    }
}

// Function to encrypt the plaintext using Playfair cipher
void encryptPlayfair(char *plaintext, char *ciphertext) {
    preprocessPlaintext(plaintext);

    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        encryptPair(&plaintext[i], &plaintext[i + 1]);
    }

    strcpy(ciphertext, plaintext);
}

// Main function
int main() {
    char plaintext[500] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[500];

    printf("Plaintext: %s\n", plaintext);

    // Encrypt the plaintext
    encryptPlayfair(plaintext, ciphertext);

    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

