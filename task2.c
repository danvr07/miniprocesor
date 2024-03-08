#include <stdio.h>

#define ushort 16
#define MAX 16
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
    int x = 0;  // contor operatii
    char opr[MAX];
    scanf("%u", &inst);

    // Se calculeaza numarul de instructiuni

    N = inst;
    N = N >> (dim_int - 3);
    N += 1;

    op = inst << 3;  //  se scot primii 3 biti care reprezina numarul instructiunilor

    // folosind functia "is_set" se cauta instructiunile
    // se salveaza in vectorul 'opr'

    for (k = POZ_1, j = POZ_2, x = 0; k > POZ_1 - N * 2; k = k - 2, j = j - 2, x++) {
        if (is_set(op, k) == 0 && is_set(op, j) == 0)
            opr[x] = '+';
        if (is_set(op, k) == 0 && is_set(op, j) == 1)
            opr[x] = '-';
        if (is_set(op, k) == 1 && is_set(op, j) == 0)
            opr[x] = '*';
        if (is_set(op, k) == 1 && is_set(op, j) == 1)
            opr[x] = '/';
    }

    // Se calculeaza dimensiunea

    dim = op << N * 2;
    dim = dim >> nr_byte;
    dim += 1;

    unsigned short n = 0;
    int i = 0;
    unsigned short formnr = ((N + 1) * dim / ushort);

    // Se deduce cate numere unsigned short se vor scana

    if ((N + 1) * dim % ushort == 0) {
        formnr = formnr;
    } else {
        formnr += 1;
    }

    // Se scaneaza numerele
    // Se salveaza in vectorul arr

    int arr[MAX];
    for (i = 0; i < formnr; i++) {
        scanf("%hu", &n);
        arr[i] = n;
    }

    int operanzi[MAX];
    unsigned short nrr = 0;
    k = 0;  // contor operanzi

    // Se depisteaza operanzii

    for (i = 0; i < formnr; i++) {
        for (unsigned int j = 0; j < ushort; j = j + dim) {
            nrr = arr[i];
            nrr = nrr << j;
            nrr = nrr >> (ushort - dim);
            operanzi[k] = nrr;
            k++;
        }
    }

    i = 0;
    j = 0;
    int rez = 0;

    // Se executa operatiile in ordinea in care sunt scrise

    while (j < N) {
        if (j == 0) {
            if (opr[j] == '*')
                rez = operanzi[i] * operanzi[i + 1];
            if (opr[j] == '+')
                rez = operanzi[i] + operanzi[i + 1];
            if (opr[j] == '-')
                rez = operanzi[i] - operanzi[i + 1];
            if (opr[j] == '/')
                rez = operanzi[i] / operanzi[i + 1];
        } else {
            if (opr[j] == '*')
                rez *= operanzi[i + 1];
            if (opr[j] == '+')
                rez += operanzi[i + 1];
            if (opr[j] == '-')
                rez -= operanzi[i + 1];
            if (opr[j] == '/')
                rez /= operanzi[i + 1];
        }
        j++;
        i++;
    }

    printf("%d\n", rez);

    return 0;
}
