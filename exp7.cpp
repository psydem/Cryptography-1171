#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to count character frequencies
void countFrequencies(char *ciphertext, int freq[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) { // Check for printable characters
            freq[(int)ciphertext[i]]++;
        }
    }
}

// Function to print frequencies
void printFrequencies(int freq[]) {
    printf("Character frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d\n", i, freq[i]);
        }
    }
}

// Function to decrypt using a given substitution table
void decrypt(char *ciphertext, char *plaintext, char substitution[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            plaintext[i] = substitution[(int)ciphertext[i]];
        } else {
            plaintext[i] = ciphertext[i]; // Leave non-printable characters as is
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the string
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 "
                        "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* "
                        ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 "
                        "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    int freq[256] = {0};
    char plaintext[strlen(ciphertext) + 1]; // Decrypted message
    char substitution[256]; // Substitution table

    // Initialize substitution table
    for (int i = 0; i < 256; i++) {
        substitution[i] = i; // Identity mapping by default
    }

    // Count character frequencies
    countFrequencies(ciphertext, freq);

    // Print character frequencies
    printFrequencies(freq);

    // Manually set substitutions based on frequency analysis and patterns
    // Example mappings based on the problem description
    substitution['‡'] = 'e'; // Most frequent, likely 'e'
    substitution['5'] = 't'; // Guessed from "the"
    substitution['3'] = 'h'; // Guessed from "the"
    substitution['8'] = 'a'; // Guessed from context

    // Decrypt the message
    decrypt(ciphertext, plaintext, substitution);

    printf("\nDecrypted message:\n%s\n", plaintext);

    return 0;
}

