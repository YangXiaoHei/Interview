//
//  main.c
//  找到链表倒数第k个结点
//
//  Created by YangHan on 2018/1/31.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef void(*printImp)(void *);
typedef struct Node_ {
    void *item;
    printImp imp;
    struct Node_ *next;
} _Node;
typedef _Node *Node;

void print(char *c) {
    printf("%c ", *c);
}
void _printForward(Node header) {
    while (header != NULL) {
        (*header->imp)(header->item);
        header = header->next;
    }
}
void printForward(Node header) {
    _printForward(header);
    printf("\n");
}
char *charGenerate(char c) {
    char *cc = calloc(1, sizeof(char));
    *cc = c;
    return cc;
}
Node initList(int N) {
    Node header = calloc(1, sizeof(_Node));
    Node h = header; int i = 0;
    while (N--) {
        Node n = calloc(1, sizeof(_Node));
        n->item = charGenerate('A' + i++);
        n->imp = (printImp)&print;
        h->next = n;
        h = h->next;
    }
    h = header->next;
    free(header);
    return h;
}
Node selectInList(Node header, int k) {
    Node slow = header, fast = header;
    while (--k) {
        fast = fast->next;
        if (fast == NULL) {
            printf("索引 %d 越界\n", k);
            return NULL;
        }
    }
    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
void _destoryList(Node header) {
    if (header == NULL) return;
    _destoryList(header->next);
    free(header->item);
    free(header);
}
void destoryList(Node *header) {
    _destoryList(*header);
    *header = NULL;
}

int main(int argc, const char * argv[]) {
    Node header = initList(10);
    printForward(header);
    for (int i = 1; i <= 10; i++) {
        printf("倒数第 %d 个结点是 %c\n", i, *(char *)(selectInList(header, i)->item));
    }
    destoryList(&header);
}
/**
 *   A B C D E F G H I J
     倒数第 1 个结点是 J
     倒数第 2 个结点是 I
     倒数第 3 个结点是 H
     倒数第 4 个结点是 G
     倒数第 5 个结点是 F
     倒数第 6 个结点是 E
     倒数第 7 个结点是 D
     倒数第 8 个结点是 C
     倒数第 9 个结点是 B
     倒数第 10 个结点是 A
 */
