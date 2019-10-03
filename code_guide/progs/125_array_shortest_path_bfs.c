#include "ds.h"

void move(int *m, int *map, int r, int c, int pre, int i, int j, queue *rq, queue *cq)
{
    if (i < 0 || i >= r || j < 0 || j >= c || !m[i * c + j] || map[i * c + j])
        return;

    map[i * c + j] = pre + 1;
    queue_enqueue(rq, i);
    queue_enqueue(cq, j);
}

int min_path(int *m, int r, int c)
{
    queue *rq = queue_create();
    queue *cq = queue_create();
    int *map = malloc(sizeof(int) * r * c);

    queue_enqueue(rq, 0);
    queue_enqueue(cq, 0);
    map[0 * c + 0] = 1;

    int i, j;
    while (!queue_empty(rq)) {
        i = queue_dequeue(rq);
        j = queue_dequeue(cq);
        if (i == r - 1 && j == c - 1)
            break;
        
        move(m, map, r, c, map[i * c + j], i, j + 1, rq, cq);
        move(m, map, r, c, map[i * c + j], i + 1, j, rq, cq);
        move(m, map, r, c, map[i * c + j], i - 1, j, rq, cq);
        move(m, map, r, c, map[i * c + j], i, j - 1, rq, cq);
    }
    int res = map[(r - 1) * c + c - 1];
    free(map);
    queue_release(&rq);
    queue_release(&cq);
    return res;
}

int main()
{
    int m[] = {
        1, 0, 1, 1, 1,
        1, 0, 1, 0, 1,
        1, 1, 1, 0, 1,
        0, 0, 1, 1, 1
    };
    int r = 4, c = 5;
    printf("%d\n", min_path(m, r, c));
}
