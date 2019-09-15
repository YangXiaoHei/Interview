#include "ds.h" 

void print_edge(int *m, int r, int c, int ulx, int uly, int drx, int dry)
{
    if (ulx == drx) {
        for (int i = uly; i <= dry; i++)
            printf("%-3d", m[ulx * c + i]);
    } else if (uly == dry) {
        for (int i = ulx; i <= drx; i++)
            printf("%-3d", m[i * c + uly]);
    } else {
        int x = ulx, y = uly;
        while (y < dry) {
            printf("%-3d", m[x * c + y]);
            y++;
        }
        while (x < drx) {
            printf("%-3d", m[x * c + y]);
            x++;
        }
        while (y > uly) {
            printf("%-3d", m[x * c + y]);
            y--;
        }
        while (x > ulx) {
            printf("%-3d", m[x * c + y]);
            x--;
        }
    }
}

void spiral_print(int *m, int r, int c)
{
    if (!m || r <= 0 || c <= 0)
        return;

    int ulx = 0, uly = 0, drx = r - 1, dry = c - 1;
    while (ulx <= drx && uly <= dry)
        print_edge(m, r, c, ulx++, uly++, drx--, dry--);
    printf("\n");
}

int main()
{
    int r = 5, c = 6;
    int *m = matrix_gen_(r, c);
    matrix_print_(m, r, c);    
    spiral_print(m, r, c);
}
