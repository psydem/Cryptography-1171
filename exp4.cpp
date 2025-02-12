#include <stdio.h>
#include <string.h>
#include <ctype.h>

void polyalphabeticCipher(char *text, char *key) {
    int keyLength = strlen(key);
    for (int i = 0, j = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + (key[j % keyLength] - base)) % 26 + base;
            j++;
        }
    }
}

int main() {
    char text[100], key[100];

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the key: ");
    scanf("%s", key);

    polyalphabeticCipher(text, key);
    printf("Encrypted text: %s\n", text);

    return 0;
}

