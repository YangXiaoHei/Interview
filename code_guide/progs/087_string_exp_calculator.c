#include "ds.h"

static const int support_optr_count = 7;

typedef enum optr_type {
    optr_add = 0,       /* 加 */
    optr_sub,           /* 减 */
    optr_mul,           /* 乘 */
    optr_div,           /* 除 */
    optr_left,          /* 左括号 */
    optr_right,         /* 右括号 */
    optr_placeholder    /* 占位符 */
} optr_type;

/* 运算符优先级表 */
static char rank[support_optr_count * support_optr_count] = {
            /* +    -     *    /    (    )    ;  */
    /* + */   '<', '<',  '>', '>', '>', '<', '<',
    /* - */   '<', '<',  '>', '>', '>', '<', '<',
    /* * */   '<', '<',  '<', '<', '>', '<', '<',
    /* / */   '<', '<',  '<', '<', '>', '<', '<',
    /* ( */   '>', '>',  '>', '>', '>', '=', ' ',
    /* ) */   ' ', ' ',  ' ', ' ', ' ', ' ', ' ',
    /* ; */   '>', '>',  '>', '>', '>', ' ', '='
};

/* 字符转换到坐标 */
static int optr_to_type[256] = {
    ['+'] = optr_add,
    ['-'] = optr_sub,
    ['*'] = optr_mul,
    ['/'] = optr_div,
    ['('] = optr_left,
    [')'] = optr_right,
    [';'] = optr_placeholder
};

/* 是否是操作数 */
static inline int is_opnd(char c)
{
    return c == '.' || (c >= '0' && c <= '9');
}

/* 获取操作数 */
static inline double get_opnd(char **cur)
{
    char *end = NULL;
    char *beg = *cur;
    double res = strtod(beg, &end); 
    *cur = end;
    return res;
}

/* 获取操作符 */
static inline char get_optr(char **cur)
{
    char res = **cur;
    char *end = *cur + 1;
    *cur = end;
    return res;
}

/* 判断是否括号匹配 */
static int parenthese_valid(const char *str)
{
    int status = 0;
    for (char *p = (char *)str; *p; p++) {
        if (*p != '(' && *p != ')')
            continue;
        
        if (*p == ')' && --status < 0)
            return 0;
        
        if (*p == '(')
            status++;
    }
    return status == 0;
}

/* 判断是否是负号前缀 */
static inline int is_prefix(char *beg, char *cur)
{
    if (beg == cur && *cur == '-')
        return 1;

    if (cur[0] == '-') {
        if (cur[-1] == '+' ||
            cur[-1] == '-' ||
            cur[-1] == '*' ||
            cur[-1] == '/' ||
            cur[-1] == '(')
            return 1;
    }
    return 0;
}

/* 根据运算符号执行相应的计算 */
static inline double calculate_core(double d1, double d2, char optr)
{
    double res = 0;
    switch (optr) {
        case '+' : res = d1 + d2; break;
        case '-' : res = d1 - d2; break;
        case '*' : res = d1 * d2; break;
        case '/' : res = d1 / d2; break;
        default: 
           printf("optr=%c invalid!\n", optr);
           exit(1);
    }
    return res;
}

/* 删除空格 */
void remove_blank(char *str)
{
    int i = 0;
    for (char *p = str; *p; p++) {
        if (*p != ' ')
            str[i++] = *p;
    }
    str[i] = 0;
}

/* 解析表达式, 并求值, 双栈法 */
double calculate(const char *exp)
{
    if (!exp || !*exp)
        return 0;
    
    int explen = strlen(exp);
    char *expbuf = malloc(explen + 1 + 1);
    snprintf(expbuf, explen + 1 + 1, "%s;", exp);

    // 删除空格
    remove_blank(expbuf);

    // 判断是否括号匹配 
    if (!parenthese_valid(exp))
        return 0;

    printf("%s = ", exp);

    // 操作数栈
    double *opnd_stack = malloc(sizeof(double) * explen);
    int opnd_size = 0;

    // 操作符栈
    char *optr_stack = malloc(sizeof(double) * explen);
    int optr_size = 0;

    // 占位符
    optr_stack[optr_size++] = ';';

    int neg_prefix = 0;
    char *cur = expbuf;
    while (optr_size) {
        if (neg_prefix) { /* 负号前缀 */
            opnd_stack[opnd_size++] = get_opnd(&cur);
            neg_prefix = !neg_prefix;
        } else if (is_opnd(*cur)) { /* 读取操作数 */
            opnd_stack[opnd_size++] = get_opnd(&cur);
        } else {
            if (is_prefix(expbuf, cur)) {  /* 发现负号前缀 */
                neg_prefix = 1;
                continue;
            } 
            char top = optr_stack[optr_size - 1];
            char will = *cur;
            char r = rank[optr_to_type[top] * support_optr_count + optr_to_type[will]];

            /* 比较优先级 */
            switch (r) {
                case '>' : {
                    optr_stack[optr_size++] = get_optr(&cur);
                } break;
                case '<' : {
                    top = optr_stack[--optr_size];
                    double n2 = opnd_stack[--opnd_size]; 
                    double n1 = opnd_stack[--opnd_size];
                    double res = calculate_core(n1, n2, top);
                    opnd_stack[opnd_size++] = res;
                } break;
                case '=' : {
                    ++cur;
                    optr_size--;
                } break;
            }
        }
    }

    double res = opnd_stack[--opnd_size];
    free(opnd_stack);
    free(optr_stack);
    free(expbuf);
    return res;
}

int main(int argc, char *argv[])
{
    printf("%.3f\n", calculate("1 + 2"));
    printf("%.3f\n", calculate("1 + 2 * 3"));
    printf("%.3f\n", calculate("(1 + 2) * 3"));
    printf("%.3f\n", calculate("(-1 + -2) * 3"));
    printf("%.3f\n", calculate("((-1 + 5) * (3 - 9)) / (8.9 + 1.1)"));
    printf("%.3f\n", calculate("-3"));
    printf("%.3f\n", calculate("3"));
    printf("%.3f\n", calculate("1 - 2 * 3"));
    printf("%.3f\n", calculate("1 - -2 * 3"));
    printf("%.3f\n", calculate("1 - -2 * -3"));
    printf("%.3f\n", calculate("(1 - -2) * -3"));

    // ????
    /* printf("%.3f\n", calculate("-(1 - -2) * -3")); */
}
