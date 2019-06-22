#include <stdio.h>
#include <string.h>

char cnt[256] = { 0 };
int loc = 1;
char appear_only_once(char c)
{
    if (cnt[c] > 0)
        cnt[c] = -1;
    else if (cnt[c] == 0)
       cnt[c] = loc;
    loc++;
    int min_idx = (1L << 31) - 1;
    int minc = 0;
    for (int i = 0; i < 256; i++) {
        if (cnt[i] > 0 && cnt[i] < min_idx) {
            min_idx = cnt[i];
            minc = i;
        }
    }
    return minc;
}

int main(int argc, char *argv[])
{
    char *str = "google";
    for (char *p = str; *p; p++)
        printf("%c\n", appear_only_once(*p));
}

    
