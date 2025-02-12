#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to prepare the Playfair cipher key matrix
void generateKeyMatrix(char *key, char matrix[5][5]) {
    int used[26] = {0};
    int i, j, k = 0;

    // Mark 'J' as already used, as we use 'I' and 'J' interchangeably
    used['J' - 'A'] = 1;

    // Fill the matrix with the key
    for (i = 0; i < strlen(key); i++) {
        if (!used[toupper(key[i]) - 'A']) {
            matrix[k / 5][k % 5] = toupper(key[i]);
            used[toupper(key[i]) - 'A'] = 1;
            k++;
        }
    }

    // Fill the remaining letters of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            k++;
        }
    }
}

// Function to find the position of a character in the key matrix
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat 'I' and 'J' as the same
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decrypt a Playfair cipher pair
void decryptPair(char matrix[5][5], char *a, char *b) {
    int row1, col1, row2, col2;

    findPosition(matrix, *a, &row1, &col1);
    findPosition(matrix, *b, &row2, &col2);

    if (row1 == row2) {
        // Same row: move left
        *a = matrix[row1][(col1 + 4) % 5];
        *b = matrix[row2][(col2 + 4) % 5];
    } else if (col1 == col2) {
        // Same column: move up
        *a = matrix[(row1 + 4) % 5][col1];
        *b = matrix[(row2 + 4) % 5][col2];
    } else {
        // Rectangle: swap columns
        *a = matrix[row1][col2];
        *b = matrix[row2][col1];
    }
}

// Function to decrypt the ciphertext using the Playfair cipher
void decryptPlayfair(char *ciphertext, char *key, char *plaintext) {
    char matrix[5][5];
    generateKeyMatrix(key, matrix);

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        decryptPair(matrix, &ciphertext[i], &ciphertext[i + 1]);
    }
    strcpy(plaintext, ciphertext);
}

// Main function
int main() {
    char key[] = "PLAYFAIR"; // Example key
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONECUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[500];

    // Decrypt the ciphertext
    decryptPlayfair(ciphertext, key, plaintext);

    // Output the plaintext
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted Plaintext: %s\n", plaintext);

    return 0;
}

