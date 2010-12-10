#include "rand.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

enum USE
{
    INICIALIZAR,
    ARQUIVO,
    PADRAO
} use = INICIALIZAR;

FILE *f = NULL;

int aleat(int min, int max)
{
    if (use == INICIALIZAR) {
        f = fopen("/dev/urandom", "r");
        if (!f) {
            f = fopen("/dev/random", "r");
        }
        if (f) {
            use = ARQUIVO;
        } else {
            srand(time(0));
            use = PADRAO;
        }
    }
    int buffer;
    if (use == ARQUIVO) {
        fread(&buffer, sizeof(int), 1, f);
    } else if (use == PADRAO) {
        buffer = rand();
    }
    if (buffer < 0)
        buffer *= -1;
    return buffer % (1 + max - min) + min;
}
