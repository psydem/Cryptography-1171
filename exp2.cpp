#include <stdio.h>
#include <string.h>
#include <ctype.h> // Include the library for isalpha() and isupper()

void monoalphabeticCipher(char *text, char *key) {
    char mapUpper[26], mapLower[26];

    // Create mapping for upper and lower case letters
    for (int i = 0; i < 26; i++) {
        mapUpper[i] = toupper(key[i]);
        mapLower[i] = tolower(key[i]);
    }

    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = mapUpper[text[i] - 'A'];
        } else if (islower(text[i])) {
            text[i] = mapLower[text[i] - 'a'];
        }
    }
}

int main() {
    char text[100], key[27];

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove the newline character

    printf("Enter the substitution key (26 characters): ");
    scanf("%s", key);

    monoalphabeticCipher(text, key);
    printf("Encrypted text: %s\n", text);

    return 0;
}

