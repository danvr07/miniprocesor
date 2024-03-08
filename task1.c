#include <stdio.h>

#define POZ_1 31  // primul byte din nr
#define POZ_2 30  // al doilea byte din nr
#define dim_int 32
#define nr_byte 28  // nr de biti de la dimensiune pana la sfarsit

int is_set(unsigned int byte, int k) {
    int mask = (1 << k);
    return (byte & mask) != 0;
}

int main() {
    unsigned int inst = 0, N = 0, op = 0, dim = 0;
    int k = 0, j = 0;
    scanf("%u", &inst);

    // Se calculeaza numarul de instructiuni

    N = inst;
    N = N >> (dim_int-3);
    N += 1;

    printf("%u ", N);

    op = inst << 3;  // se scot primii 3 biti care reprezina numarul instructiunilor

    // folosind functia "is_set" se cauta instructiunile

    for (k = POZ_1, j = POZ_2; k > POZ_1 - N*2 ; k = k - 2, j = j - 2) {
        if (is_set(op, k) == 0 && is_set(op, j) == 0)
            printf("+ ");
        if (is_set(op, k) == 0 && is_set(op, j) == 1)
            printf("- ");
        if (is_set(op, k) == 1 && is_set(op, j) == 0)
            printf("* ");
        if (is_set(op, k) == 1 && is_set(op, j) == 1)
            printf("/ ");
    }

    // Se calculeaza dimensiunea

    dim = op << N*2;
    dim = dim >> nr_byte;
    dim += 1;

    printf("%u\n", dim);

    return 0;
}
