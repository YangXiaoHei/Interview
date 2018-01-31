//
//  main.c
//  给定链表头和待删除结点，在O(1)时间内删除该结点
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
typedef _Node * Node;

void print(char *c) {
    printf("%c ", *c);
}
char *charGenerate(char c) {
    char *cc = calloc(1, sizeof(char));
    cc[0] = c;
    return cc;
}
Node header() {
    return calloc(1, sizeof(_Node));
}
Node node(void *item, Node next, printImp imp) {
    Node n = calloc(1, sizeof(_Node));
    n->item = item;
    n->next = next;
    n->imp = imp;
    return n;
}
Node initList(int N) {
    Node n = header();
    Node h = n; int i = 0;
    while (N--) {
        h->next = node(charGenerate('A' + i++), NULL, (printImp)*print);
        h = h->next;
    }
    h = n->next;
    free(n);
    return h;
}
void _printForward(Node h) {
    while (h) {
        (*h->imp)(h->item);
        h = h->next;
    }
}
/**
 *  假定待删除的结点一定在以 header 为头结点的链表中，函数内部不作这项检查
 */
Node delete(Node header, Node del) {
    if (header == NULL || del == NULL) {
        printf("参数不合法!");
        return header;
    }
    printf("在链表中删除 %c \n", *(char *)(del->item));
    if (header == del)  {
        Node h = header->next;
        free(header->item);
        free(header);
        return h;
    }
    if (del->next == NULL) { // 尾结点
        Node h = header;
        while (h->next != del) h = h->next;
        free(del->item);
        free(del);
        h->next = NULL;
    } else { // 不是尾结点
        free(del->item);
        del->item = del->next->item;
        Node h = del->next;
        del->next = del->next->next;
        free(h);
    }
    return header;
}
Node selectInList(Node header, int k) {
    int kk = k;
    while (kk--) {
        header = header->next;
        if (header == NULL) {
            printf("%d 所指定的索引越界\n", k);
            return NULL;
        }
    }
    return header;
}
void printForward(Node h) {
    _printForward(h);
    printf("\n");
}
void _destoryList(Node h) {
    if (h == NULL) return;
    _destoryList(h->next);
    free(h->item);
    free(h);
}
void destoryList(Node *h) {
    _destoryList(*h);
    *h = NULL;
}
int main(int argc, const char * argv[]) {
    
    Node header = initList(10);
    printForward(header);
    
    header = delete(header, selectInList(header, 4));
    printForward(header);

    header = delete(header, selectInList(header, 8));
    printForward(header);

    header = delete(header, selectInList(header, 2));
    printForward(header);

    header = delete(header, selectInList(header, 3));
    printForward(header);
    
    header = delete(header, selectInList(header, 0));
    printForward(header);
    
    header = delete(header, selectInList(header, 4));
    printForward(header);

    header = delete(header, selectInList(header, 0));
    printForward(header);
    
    destoryList(&header);
    return 0;
}
/**
 *   A B C D E F G H I J
     在链表中删除 E
     A B C D F G H I J
     在链表中删除 J
     A B C D F G H I
     在链表中删除 C
     A B D F G H I
     在链表中删除 F
     A B D G H I
     在链表中删除 A
     B D G H I
     在链表中删除 I
     B D G H
     在链表中删除 B
     D G H
 */
