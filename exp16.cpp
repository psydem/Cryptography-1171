#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Standard English letter frequency (A-Z)
double englishFreq[] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 
                        6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 
                        7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 
                        0.978, 2.360, 0.150, 1.974, 0.074};

// Structure to store possible mappings
typedef struct {
    char mapping[26]; // Cipher-to-plain mapping
    double score;
} Candidate;

// Function to count letter frequency in ciphertext
void countFrequency(char *text, int freq[26]) {
    for (int i = 0; i < 26; i++) freq[i] = 0;
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            freq[toupper(text[i]) - 'A']++;
        }
    }
}

// Function to map ciphertext letters to plaintext letters based on frequency
void createMapping(int cipherFreq[26], char mapping[26]) {
    int used[26] = {0}; // Track used letters
    int sortedCipher[26], sortedPlain[26];

    // Sort ciphertext letters by frequency (descending)
    for (int i = 0; i < 26; i++) sortedCipher[i] = i;
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (cipherFreq[sortedCipher[i]] < cipherFreq[sortedCipher[j]]) {
                int temp = sortedCipher[i];
                sortedCipher[i] = sortedCipher[j];
                sortedCipher[j] = temp;
            }
        }
    }

    // Sort standard English frequencies (descending)
    for (int i = 0; i < 26; i++) sortedPlain[i] = i;
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (englishFreq[sortedPlain[i]] < englishFreq[sortedPlain[j]]) {
                int temp = sortedPlain[i];
                sortedPlain[i] = sortedPlain[j];
                sortedPlain[j] = temp;
            }
        }
    }

    // Create mapping based on frequency order
    for (int i = 0; i < 26; i++) {
        mapping[sortedCipher[i]] = 'A' + sortedPlain[i];
        used[sortedPlain[i]] = 1;
    }
}

// Function to decrypt using the generated mapping
void decryptText(char *ciphertext, char *plaintext, char mapping[26]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = mapping[toupper(ciphertext[i]) - 'A'];
            if (islower(ciphertext[i])) plaintext[i] = tolower(plaintext[i]);
        } else {
            plaintext[i] = ciphertext[i]; // Preserve spaces/punctuation
        }
    }
    plaintext[len] = '\0';
}

// Function to score decrypted text based on letter frequency
double scoreText(char *text) {
    int letterCounts[26] = {0}, totalLetters = 0;
    double score = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            letterCounts[toupper(text[i]) - 'A']++;
            totalLetters++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (totalLetters > 0) {
            double frequency = (double)letterCounts[i] / totalLetters * 100;
            score += frequency * englishFreq[i]; // Weighted sum
        }
    }
    return score;
}

// Function to compare candidates for sorting
int compare(const void *a, const void *b) {
    return ((Candidate *)b)->score - ((Candidate *)a)->score > 0 ? 1 : -1;
}

int main() {
    char ciphertext[500], plaintext[500];
    int numResults;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline

    printf("Enter the number of top results to display: ");
    scanf("%d", &numResults);

    Candidate candidates[10]; // Store top mappings

    for (int i = 0; i < numResults; i++) {
        int freq[26];
        char mapping[26];

        countFrequency(ciphertext, freq);
        createMapping(freq, mapping);
        decryptText(ciphertext, plaintext, mapping);

        strcpy(candidates[i].mapping, mapping);
        candidates[i].score = scoreText(plaintext);
    }

    qsort(candidates, numResults, sizeof(Candidate), compare);

    printf("\nTop %d possible plaintexts:\n", numResults);
    for (int i = 0; i < numResults; i++) {
        decryptText(ciphertext, plaintext, candidates[i].mapping);
        printf("Rank %d (Score: %.2f): %s\n", i + 1, candidates[i].score, plaintext);
    }

    return 0;
}

