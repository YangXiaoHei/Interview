#include "ds.h"

ht *record = NULL;

#define HT_INSERT(h, k, v) ht_insert((h), (long)(k), (long)v)
#define HT_CONTAIN(h, k) ht_contain((h), (long)(k))
#define HT_GET_HT(h, k) ((ht *)ht_get((h), (long)(k)))
#define HT_GET_N(h, k) ((treenode *)ht_get((h), (long)(k)))

void create_record(treenode *);
void init_treenode_record(treenode *);
void set_record(treenode *);
void set_head_record(treenode *, treenode *);
void set_subtree_record(treenode *);
void set_left(treenode *, treenode *, treenode *);
void set_right(treenode *, treenode *, treenode *);

long normal_hash(long key)
{
    return key;
}

void create_record(treenode *root)
{
    record = ht_create(normal_hash);
    init_treenode_record(root);
    set_record(root);
}

/* 树中每个节点都挂上一个哈希表 */
void init_treenode_record(treenode *root)
{
    if (!root)
        return;

    ht *node_ht = ht_create(normal_hash);
    HT_INSERT(record, root, node_ht);
    init_treenode_record(root->left);
    init_treenode_record(root->right);
}

void set_record(treenode *root)
{
    if (!root)
        return;

    /*
     * 左子树中每个节点和 root 的最低公共祖先，
     * 都将是 root
     */
    set_head_record(root->left, root);
    /*
     * 右子树中每个节点和 root 的最低公共祖先,
     * 都将是 root
     */
    set_head_record(root->right, root);
    /*
     * 对于 root 的左右子树 root->left 和 root->right
     * 对于左子树中的每个节点, 分别遍历右子树中的每个节点,
     * 即对于 L1, L2, L3... 分别遍历 R1, R2, R3...
     * 建立起 L1->R1, L1->R2, L1->R3, L2->R1, L2->R2, L2->R3 的每个对
     * 对于每一个这样的映射对, 他们的最低公共祖先都将是 root
     */
    set_subtree_record(root);

    set_record(root->left);
    set_record(root->right);
}

void set_head_record(treenode *root, treenode *head)
{
    if (!root)
        return;

    HT_INSERT(HT_GET_HT(record, root), head, head);
#ifdef DEBUG
    printf("head_record {%ld %ld} -> %ld\n", root->val, head->val, head->val);
#endif
    set_head_record(root->left, head);
    set_head_record(root->right, head);
}

/* 遍历左子树中所有节点, 同时对于左子树中某个节点 Li, 遍历右子树中所有节点 */
void set_left(treenode *l, treenode *r, treenode *h)
{
    if (!l)
       return;

    set_right(l, r, h);
    set_left(l->left, r, h);
    set_left(l->right, r, h);
}

/* 对于左子树中某个节点 Li, 遍历右子树中所有节点 Rj, 建立 {Li, Rj} -> h 的映射关系 */
void set_right(treenode *l, treenode *r, treenode *h)
{
    if (!r)
        return;

    HT_INSERT(HT_GET_HT(record, l), r, h);
#ifdef DEBUG
    printf("set_right {%ld %ld} -> %ld\n",  l->val, r->val, h->val);
#endif
    set_right(l, r->left, h);
    set_right(l, r->right, h);
}

void set_subtree_record(treenode *root)
{
    if (!root)
        return;

    set_left(root->left, root->right, root);
    set_subtree_record(root->left);    
    set_subtree_record(root->right);    
}

treenode *query(treenode *n1, treenode *n2)
{
    if (n1 == n2)
        return n1;
    
    if (HT_CONTAIN(record, n1)) {
        ht *h = HT_GET_HT(record, n1);
        if (HT_CONTAIN(h, n2)) 
            return HT_GET_N(h, n2);
    } 

    if (HT_CONTAIN(record, n2)) {
        ht *h = HT_GET_HT(record, n2);
        if (HT_CONTAIN(h, n1)) 
            return HT_GET_N(h, n1);
    } 

    return NULL;
}

treenode *get_kth_node(treenode *root, int k)
{
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))

    if (!root || k < 0)
        return NULL;

    treenode *target = NULL;
    stack *s = stack_create();
    while (!stack_empty(s) || root) {
        if (root) {
            PUSH(s, root);
            root = root->left;
        } else {
            root = POP(s);
            if (k-- <= 0) {
                target = root;
                break;
            }
            root = root->right;
        }
    }
    stack_release(&s);
    return target;
}

void gen_two_treenode(treenode *root, int size, treenode **n1, treenode **n2)
{
    int k = randWithRange(0, size);
    int m = randWithRange(0, size);
    *n1 = get_kth_node(root, k);
    *n2 = get_kth_node(root, m);
}

int main(int argc, char *argv[])
{
    /* treenode *root = bst_create(5); */
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->right = N(3);
    root->left->left = N(4);
    root->left->right = N(5);
    root->right->left = N(6);
    root->right->right = N(7);
    root->left->left->left = N(8);
    root->left->left->right = N(9);
    root->left->right->left = N(10);
    tree_draw(root);
    create_record(root);

#ifdef DEBUG
        for (htnode *cur = record->slot[i]; cur; cur = cur->next) {
            treenode *n1 = (treenode *)cur->key;
            ht *subht = (ht *)cur->val;
            printf("%3ld (%lu) \n", n1->val, n1);
            for (int j = 0; j < subht->bucket; j++) {
                for (htnode *subcur = subht->slot[j]; subcur; subcur = subcur->next) {
                    treenode *n2 = (treenode *)subcur->key;
                    treenode *parent = (treenode *)subcur->val;
                    printf("\t%3ld (%lu) -> parent %3ld (%lu) \n", n2->val, n2, parent->val, parent);
                }
            }
        } 
    }
#endif

    treenode *n1 = NULL, *n2 = NULL;
    gen_two_treenode(root, 10, &n1, &n2);
    printf("n1 = %ld (%lu) n2 = %ld (%lu)\n", n1->val, (unsigned long)n1, n2->val, (unsigned long)n2);

    treenode *common = query(n1, n2);
    if (common)
        printf("common %ld\n", common->val);
    else
        printf("common not exist!\n");
}
