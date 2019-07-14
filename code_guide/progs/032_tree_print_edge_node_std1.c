#include "ds.h"

void set_edge_map(treenode *root, int level, treenode **map)
{
    if (!root)
        return;

    if (!map[level * 2 + 0])
        map[level * 2 + 0] = root;
    map[level * 2 + 1] = root;

    set_edge_map(root->left, level + 1, map);
    set_edge_map(root->right, level + 1, map);
}

void print_middle_leaf(treenode *root, int level, treenode **map)
{
    if (!root)
       return;

    if (!root->left && !root->right && root != map[level * 2 + 0] && root != map[level * 2 + 1]) 
        printf("%-3ld", root->val);

    print_middle_leaf(root->left, level + 1, map);
    print_middle_leaf(root->right, level + 1, map);
}

void print_edge_node(treenode *root)
{
    if (!root)
        return;

    int h = tree_height(root);
    treenode **map = malloc(sizeof(treenode **) * (h * 2));
    for (int i = 0; i < h; i++) {
        map[i * 2 + 0] = NULL;
        map[i * 2 + 1] = NULL;
    }

    set_edge_map(root, 0, map);


    for (int i = 0; i < h; i++) 
        printf("%-3ld", map[i * 2 + 0]->val);

#ifdef DEBUG
    for (int i = 0; i < h; i++) {
        printf("%-3ld", map[i * 2 + 0] ? map[i * 2 + 0]->val : -1);
        printf("%-3ld", map[i * 2 + 1] ? map[i * 2 + 1]->val : -1);
        printf("\n");
    }
#endif

    print_middle_leaf(root, 0, map);

    for (int i = h - 1; i >= 0; i--) {
        if (map[i * 2 + 0] != map[i * 2 + 1]) {
            printf("%-3ld", map[i * 2 + 1]->val);
        }
    }
    printf("\n");
    free(map);
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)

    treenode *root = N(1);
    root->left = N(2);
    root->left->right = N(4);
    root->left->right->left = N(7);
    root->left->right->right = N(8);
    root->left->right->right->right = N(11);
    root->left->right->right->right->left = N(13);
    root->left->right->right->right->right = N(14);
    root->right = N(3);
    root->right->left = N(5);
    root->right->right = N(6);
    root->right->left->left = N(9);
    root->right->left->right = N(10);
    root->right->left->left->left = N(12);
    root->right->left->left->left->left = N(15);
    root->right->left->left->left->right = N(16);
    print_edge_node(root);
}
