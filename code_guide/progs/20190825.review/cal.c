#include "ds.h"

const int optr_num = 7;
static char rank[] = {
            /* +    -    *    /   (     )   ; */
    /* + */   '<', '<', '>', '>', '>', '<', '<',
    /* - */   '<', '<', '>', '>', '>', '<', '<',
    /* * */   '<', '<', '<', '<', '>', '<', '<', 
    /* / */   '<', '<', '<', '<', '>', '<', '<', 
    /* ( */   '>', '>', '>', '>', '>', '=', ' ',
    /* ) */   '<', '<', '<', '<', ' ', ' ', ' ',
    /* ; */   '>', '>', '>', '>', '>', ' ', '='
};

static int o2t[] = {
    ['+'] = 0,
    ['-'] = 1,
    ['*'] = 2,
    ['/'] = 3,
    ['('] = 4,
    [')'] = 5,
    [';'] = 6,
};

double read_opnd(const char *beg, char **end)
{
    return strtod(beg, end);
}

char read_optr(const char *beg, char **end)
{
    *end = (char *)beg + 1;
    return *beg;
}

int is_opnd(const char *beg)
{
    return *beg >= '0' && *beg <= '9';
}

double cal(const char *str)
{
    if (!str || !*str)
        return 0;

    int len = strlen(str);
    char *buf = malloc(len + 1 + 1);
    snprintf(buf, len + 1 + 1, "%s;", str);

    char optr_stk[100]; 
    int optr_size = 0;
    double opnd_stk[100];
    int opnd_size = 0;

    optr_stk[optr_size++] = ';';
    char *p = buf;
    char *tmp = NULL;
    while (optr_size > 0) {
        if (is_opnd(p)) {
            opnd_stk[opnd_size++] = read_opnd(p, &tmp); 
            p = tmp;
        } else {
            char top = optr_stk[optr_size - 1];
            char will = read_optr(p, &tmp);
            char r = rank[o2t[top] * optr_num + o2t[will]];
            switch (r) {
                case '>' : {
                    optr_stk[optr_size++] = will;                    
                    p = tmp;
                } break;
                case '<' : {
                    double n2 = opnd_stk[--opnd_size];
                    double n1 = opnd_stk[--opnd_size];
                    double res = 0;
                    if (top == '+')
                        res = n1 + n2;
                    else if (top == '-')
                        res = n1 - n2;
                    else if (top == '*')
                        res = n1 * n2;
                    else
                        res = n1 / n2;
                    optr_size--;
                    opnd_stk[opnd_size++] = res;
                } break;
                case '=' : {
                    optr_size--;
                    p = tmp;
                } break;
                default:
                   exit(1);
            }
        }
    }
    return opnd_stk[0];
}

int main(int argc, char *argv[])
{
    printf("%.2f\n", cal("1+2"));
    printf("%.2f\n", cal("1+2*3"));
    printf("%.2f\n", cal("(1+2)*3"));
    printf("%.2f\n", cal("1/2*3"));
    printf("%.2f\n", cal("1/(2*3)"));
    printf("%.2f\n", cal("(1+2)*((4-3)/5)"));
}
