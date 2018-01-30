//
//  main.c
//  atoi和atol的实现
//
//  Created by YangHan on 2018/1/31.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/**
 *  对应的 ASCLL 码是否表示数字
 */
int _is_digit(char c) {
    return c >= '0' && c <= '9';
}
/**
 *  将诸如 "-1234543" 的字符串转换为整数类型
 *  @param s 待转换字符串
 *  @param err 转换中发生的错误
 *  @return 字符串转换后的整数
 */
int _atoi(const char *s, char **err) {
    // 空指针检测
    if (s == NULL) {
        if (err != NULL)
            *err = "null pointer";
        return 0;
    }
    // 确定符号位
    int sign = 1;
    if (!_is_digit(*s)) {  // 如果有符号位
        if      (*s == '+') sign = 1;
        else if (*s == '-') sign = -1;
        else    {
            if (err != NULL)
                *err = "invalid characters in string!";
            return 0;
        }
        ++s;
    }
    long sum = 0;
    // 遍历字符串直到...
    while (*s != '\0') {
        if (!_is_digit(*s)) { // 如果包含除数字外的字符
            if (err != NULL)
                *err = "invalid characters in string!";
            return 0;
        }
        int cur = *s - '0'; // 取出数字位
        long rel = sum * 10;
        // 检测乘法是否溢出
        if ((sign == 1 && rel > 0x7FFFFFFFL) ||
            (sign == -1 && rel > 0x80000000L)) {
            if (err != NULL)
                *err = "int overflow - multiply";
            return 0;
        }
        sum = rel + cur;
        // 检测加法是否溢出
        if ((sign == 1 && sum > 0x7FFFFFFFL) ||
            (sign == -1 && sum > 0x80000000L)) {
            if (err != NULL)
                *err = "int overflow - addition";
            return 0;
        }
        ++s; // 指针挪动一个字节
    }
    return (int)(sum * sign);
}

/**
 *  将形如 "-1231324234" 的字符串转换为整数
 *  @param s 待转换的字符串
 *  @param err 转换中发生的错误
 *  @return 字符串转换后的整数
 */
long _atol(const char *s, char **err) {
    // 确定符号位
    int sign = 1;
    if (!_is_digit(*s)) {
        if      (*s == '+') sign = 1;
        else if (*s == '-') sign = -1;
        else    {
            if (err != NULL)
                *err = "invalid character!";
            return 0;
        }
        ++s;
    }
    long sum = 0;
    // 遍历字符串
    while (*s != '\0') {
        if (!_is_digit(*s)) { // 如果碰到不是数字的位
            if (err != NULL)
                *err = "invalid character!";
            return 0;
        }
        int cur = *s - '0';
        long rel = sum * 10;
        // 乘法溢出
        if (rel / 10 != sum) {
            if (err != NULL)
                *err = "long overflow - multiply";
            return 0;
        }
        sum = rel + cur;
        // 加法溢出
        if ((sign == 1 && sum < 0) ||
            (sign == -1 && (sum < 0 && sum != 0x8000000000000000))) {
            if (err != NULL)
                *err = "long overflow - addition";
            return 0;
        }
        ++s;
    }
    return sum * sign;
}

/**
 *  测试客户端
 */
void test_atoi(const char *s) {
    char *err = NULL;
    int d = _atoi(s, &err);
    if (err == NULL) {
        printf("%d\n", d);
    } else {
        printf("cast failed : %s\n", err);
    }
}
void test_atol(const char *s) {
    char *err = NULL;
    long d = _atol(s, &err);
    if (err == NULL) {
        printf("%ld\n", d);
    } else {
        printf("cast failed : %s\n", err);
    }
}

int main(int argc, const char * argv[]) {
    test_atoi("+1234");
    test_atoi("-1234");
    test_atoi("4321");
    test_atoi("2147483647");
    test_atoi("-2147483648");
    test_atoi("2147483648");
    test_atoi("-2147483649");
    
    printf("------------------------\n");
    
    test_atol("+1234");
    test_atol("-1234");
    test_atol("4321");
    test_atol("2147483647");
    test_atol("-2147483648");
    test_atol("2147483648");
    test_atol("-2147483649");
    test_atol("9223372036854775807");
    test_atol("-9223372036854775808");
    test_atol("9223372036854775808");
    test_atol("-9223372036854775809");
    return 0;
}
/**
 *   1234
     -1234
     4321
     2147483647
     -2147483648
     cast failed : int overflow - addition
     cast failed : int overflow - addition
     ------------------------
     1234
     -1234
     4321
     2147483647
     -2147483648
     2147483648
     -2147483649
     9223372036854775807
     -9223372036854775808
     cast failed : long overflow - addition
     cast failed : long overflow - addition
 */

