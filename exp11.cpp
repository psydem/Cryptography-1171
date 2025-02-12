#include <stdio.h>
#include <math.h>
double factorial_log2(int n) {
    double log_fact = 0.0;
    for (int i = 1; i <= n; i++) {
        log_fact += log2(i);
    }
    return log_fact;
}

int main() {
    int n = 25;
    double log2_factorial = factorial_log2(n);

    printf("Approximate number of Playfair keys: 2^%.1f\n", log2_factorial);
    printf("Considering identical encryption results, unique keys: 2^79\n");

    return 0;
}

