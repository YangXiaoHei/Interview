#include "ds.h"

void print_line(int *m, int r, int c, int ulx, int uly, int drx, int dry, int f)
{
    if (f) {
        while (ulx <= drx) {
            printf("%-3d", m[ulx * c + uly]);
            /* printf("from up, [%d][%d]\n", ulx, uly); */
            ulx++, uly--;
        }
    } else {
        while (drx >= ulx) {
            printf("%-3d", m[drx * c + dry]);
            /* printf("from down, [%d][%d]\n", drx, dry); */
            drx--, dry++;
        }
    }
}

void zprint(int *m, int r, int c)
{
    if (!m || r <= 0 || c <= 0)
        return;

    int ulx = 0, uly = 0, drx = 0, dry = 0;
    int f = 0;
    while (ulx <= r - 1) {
        print_line(m, r, c, ulx, uly, drx, dry, f);
        ulx = uly == c - 1 ? ulx + 1 : ulx;
        uly = uly == c - 1 ? uly : uly + 1;
        dry = drx == r - 1 ? dry + 1 : dry;
        drx = drx == r - 1 ? drx : drx + 1;
        f = !f;
    }
    printf("\n");
}

int main()
{
    int r = randWithRange(1, 10);
    int c = randWithRange(1, 10);
    r = 4, c = 3;
    int *m = matrix_gen_(r, c);
    matrix_print_(m, r, c);
    zprint(m, r, c);
}
