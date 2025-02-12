#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// English letter frequency (A-Z): Based on standard frequency analysis
double letterFreq[] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 
                       6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 
                       0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 
                       1.974, 0.074};

// Structure to hold possible plaintexts and their scores
typedef struct {
    char plaintext[100];
    double score;
} Candidate;

// Function to decrypt using a given shift
void decrypt(char ciphertext[], int shift, char decrypted[]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            decrypted[i] = (ciphertext[i] - base - shift + 26) % 26 + base;
        } else {
            decrypted[i] = ciphertext[i]; // Keep spaces & punctuation unchanged
        }
    }
    decrypted[len] = '\0';
}

// Function to score decrypted text based on English letter frequency
double scoreText(char text[]) {
    double score = 0;
    int letterCounts[26] = {0}, totalLetters = 0;

    // Count letters in the text
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            letterCounts[toupper(text[i]) - 'A']++;
            totalLetters++;
        }
    }

    // Compute score using letter frequency
    for (int i = 0; i < 26; i++) {
        if (totalLetters > 0) {
            double frequency = (double)letterCounts[i] / totalLetters * 100;
            score += frequency * letterFreq[i]; // Weighted sum
        }
    }
    return score;
}

// Function to compare candidates for sorting (higher score = more likely)
int compare(const void *a, const void *b) {
    return ((Candidate *)b)->score - ((Candidate *)a)->score > 0 ? 1 : -1;
}

int main() {
    char ciphertext[100];
    int numResults;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline

    printf("Enter the number of top results to display: ");
    scanf("%d", &numResults);

    Candidate candidates[25];

    // Try all 25 shifts
    for (int shift = 1; shift <= 25; shift++) {
        decrypt(ciphertext, shift, candidates[shift - 1].plaintext);
        candidates[shift - 1].score = scoreText(candidates[shift - 1].plaintext);
    }

    // Sort based on frequency analysis scores
    qsort(candidates, 25, sizeof(Candidate), compare);

    // Print top N most likely plaintexts
    printf("\nTop %d possible plaintexts:\n", numResults);
    for (int i = 0; i < numResults; i++) {
        printf("Rank %d (Shift: %d, Score: %.2f): %s\n", i + 1, 
               26 - (i + 1), candidates[i].score, candidates[i].plaintext);
    }

    return 0;
}

