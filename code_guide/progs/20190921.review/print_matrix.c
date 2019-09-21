#include "ds.h"

void print_core(int *m, int r, int c, int ulx, int uly, int drx, int dry)
{
    if (uly == dry) {
        for (int i = ulx; i <= drx; i++) {
            printf("%-3d", m[i * c + uly]);
        }
    } else if (ulx == drx) {
        for (int i = uly; i <= dry; i++) {
            printf("%-3d", m[ulx * c + i]);
        }
    } else {
        int j = uly;
        while (j < dry) {
            printf("%-3d", m[ulx * c + j++]);
        }

        int i = ulx;
        while (i < drx) {
            printf("%-3d", m[i++ * c + dry]);
        }

        while (j > uly) {
            printf("%-3d", m[drx * c + j--]);
        }
        while (i > ulx) {
            printf("%-3d", m[i-- * c + uly]);
        }
    }
}

void print_matrix(int *m, int r, int c)
{
    int ulx = 0, uly = 0, drx = r - 1, dry = c - 1;
    while (ulx <= drx && uly <= dry) 
        print_core(m, r, c, ulx++, uly++, drx--, dry--);
    printf("\n");
}

int main()
{
    int r = randWithRange(1, 8);
    int c = randWithRange(1, 8);
    int *m = matrix_gen_(r, c);
    matrix_print_(m, r, c);
    print_matrix(m, r, c);
}
