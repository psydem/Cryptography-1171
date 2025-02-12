#include <stdio.h>
#include <ctype.h>
#include <string.h>

void caesarCipher(char *text, int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + k) % 26 + base;
        }
    }
}

int main() {
    char text[100];
    int k;

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the key (1-25): ");
    scanf("%d", &k);

    caesarCipher(text, k);
    printf("Encrypted text: %s\n", text);

    return 0;
}

