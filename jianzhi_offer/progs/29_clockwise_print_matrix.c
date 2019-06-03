#include <stdio.h>

typedef enum dir {
    right, down, left, up
} dir_type;

int vector[][2] = {
    [right] = { 0, 1 },
    [down]  = { 1, 0 },
    [left]  = { 0, -1 },
    [up]    = { -1, 0 },
};

#define bitset_count(n) ((n) / 8 + 1)
#define bitset_init(a, n) char a[bitset_count(n)] = { 0 }; 
#define bitset_set(b, i) (b[(i) / 8] |= (1 << ((i) % 8)))
#define bitset_clear(b, i) (b[(i) / 8] &= ~(1 << ((i) % 8)))
#define bitset_test(b, i) ((b[(i) / 8] >> ((i) % 8)) & 1)

void clockwise_print_matrix(int *matrix, int row, int col)
{
    if (!matrix || row <= 0 || col <= 0) return;

    bitset_init(a, 10000);

    int dir = right;
    int i = 0, j = 0;
    int next_i, next_j;

    while (!bitset_test(a, i * col + j) && i >= 0 && i < row && j >= 0 && j < col) {

        bitset_set(a, i * col + j);
        printf("%-3d", matrix[i * col + j]);

        next_i = i + vector[dir][0];
        next_j = j + vector[dir][1];

        if (next_i < 0 || next_i >= row || 
            next_j < 0 || next_j >= col || 
            bitset_test(a, next_i * col + next_j)) {
            dir = (dir + 1) % 4;
            i += vector[dir][0];
            j += vector[dir][1];
        } else {
            i = next_i;
            j = next_j;
        }
    }    
    printf("\n");
}

int main(int argc, char *argv[])
{
    int a[] = {
        1, 2
    };
    clockwise_print_matrix(a, 1, 2);
}
