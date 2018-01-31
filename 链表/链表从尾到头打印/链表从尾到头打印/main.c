//
//  main.c
//  链表从尾到头打印
//
//  Created by YangHan on 2018/1/31.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void(*Imp)(void *);
struct Node_ {
    void *item;
    Imp imp;
    struct Node_ * next;
};
typedef struct Node_ *Node;
void print(char *);
Node header(void);
Node node(void *, Node, Imp);
char *charGenerate(char c);
Node initList(int N);
void _printBackward(Node n);
void printBackward(Node n);
void _printForward(Node n);
void printForward(Node n);
void _destoryList(Node n);
void destoryList(Node *n);

/**
 *  自定义打印函数
 */
void print(char *c) {
    printf("%c ", *c);
}
/**
 *  创建空结点
 */
Node header(void) {
    Node n = calloc(1, sizeof(struct Node_));
    return n;
}
/**
 *  创建链表结点
 */
Node node(void *it, Node next, Imp imp) {
    Node n = calloc(1, sizeof(struct Node_));
    n->item = it;
    n->next = next;
    n->imp = imp;
    return n;
}
/**
 *  创建一个在堆上分配内存的 char
 */
char *charGenerate(char c) {
    char *cc = calloc(1, sizeof(char));
    cc[0] = c;
    return cc;
}
/**
 *  创建一个链表
 */
Node initList(int N) {
    srand((unsigned)time(NULL));
    Node h = header();
    Node n = h; int i = 0;
    while (N--) {
        n->next = node(charGenerate('A' + (i++)), NULL, (Imp)&print);
        n = n->next;
    }
    Node t = h->next;
    free(h);
    return t;
}
/**
 *  反向打印链表
 */
void printBackward(Node n) {
    printf("反向打印链表 : \n");
    _printBackward(n);
    printf("\n");
}
/**
 *  反向打印链表
 */
void _printBackward(Node n) {
    if (n == NULL) return;
    _printBackward(n->next);
    (*n->imp)(n->item);
}
/**
 *  正向打印链表
 */
void printForward(Node n) {
    printf("正向打印链表 :\n");
    _printForward(n);
    printf("\n");
}
/**
 *  正向打印链表
 */
void _printForward(Node n) {
    for (Node h = n; h != NULL; h = h->next) {
        (*h->imp)(h->item);
    }
}
/**
 *  销毁链表
 */
void destoryList(Node *n) {
    _destoryList(*n);
    *n = NULL;
}
/**
 *  销毁链表
 */
void _destoryList(Node n) {
    if (n == NULL) return;
    _destoryList(n->next);
    free(n->item);
    free(n);
}

int main(int argc, const char * argv[]) {
    Node n = initList(26);
    printForward(n);
    printBackward(n);
    destoryList(&n);
}
/**
 *   正向打印链表 :
     A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
     反向打印链表 :
     Z Y X W V U T S R Q P O N M L K J I H G F E D C B A
 */
