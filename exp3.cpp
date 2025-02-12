#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyMatrix(char *key, char keyMatrix[SIZE][SIZE]) {
    int map[26] = {0};
    int k = 0;

    for (int i = 0; key[i] && k < 25; i++) {
        if (!map[key[i] - 'a'] && key[i] != 'j') {
            keyMatrix[k / SIZE][k % SIZE] = key[i];
            map[key[i] - 'a'] = 1;
            k++;
        }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (!map[c - 'a'] && c != 'j') {
            keyMatrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }
}

void encryptPlayfair(char *plaintext, char keyMatrix[SIZE][SIZE]) {
    // Encryption logic here
    printf("Feature under development.\n");
}

int main() {
    char key[100], plaintext[100];
    char keyMatrix[SIZE][SIZE];

    printf("Enter the keyword: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    generateKeyMatrix(key, keyMatrix);
    printf("Key Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", keyMatrix[i][j]);
        }
        printf("\n");
    }

    encryptPlayfair(plaintext, keyMatrix);
    return 0;
}

