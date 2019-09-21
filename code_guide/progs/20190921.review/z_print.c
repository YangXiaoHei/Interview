#include "ds.h"

void z_print_core(int *m, int r, int c, int lx, int ly, int rx, int ry, int up)
{
    if (up) {
        for (int i = rx, j = ry; i <= lx && j >= ly; i++, j--) {
            printf("%-3d", m[i * c + j]);
        }
    } else {
        for (int i = lx, j = ly; i >= rx && j <= ry; i--, j++) {
            printf("%-3d", m[i * c + j]);
        }
    }
}

void z_print(int *m, int r, int c)
{
    int rx = 0, ry = 0, lx = 0, ly = 0;
    int up = 0;
    do {
        z_print_core(m, r, c, lx, ly, rx, ry, up);
        up = !up;
        ly = lx == r - 1 ? ly + 1 : ly;
        lx = lx == r - 1 ? lx : lx + 1;

        rx = ry == c - 1 ? rx + 1 : rx;
        ry = ry == c - 1 ? ry : ry + 1;
    } while (rx <= lx && ly <= ry);
    printf("\n");
}

int main()
{
    int r = randWithRange(1, 8);
    int c = randWithRange(1, 8);
    int *m = matrix_gen_(r, c);
    matrix_print_(m, r, c);
    z_print(m, r, c);
}
