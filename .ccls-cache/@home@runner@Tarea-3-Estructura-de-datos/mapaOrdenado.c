#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "mapaOrdenado.h"

struct AVLNode {
    Pair *pair;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
};

struct AVLTree {
    AVLNode *root;
};

int maxO(int a, int b) {
    return (a > b) ? a : b;
}

int heightO(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalanceO(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return heightO(node->left) - height(node->right);
}

Pair *createPairO(char *key, void *value) {
    Pair *newPair = malloc(sizeof(Pair));
    newPair->key = strdup(key);
    newPair->value = value;
    return newPair;
}

AVLNode *createNodeO(char *key, void *value) {
    AVLNode *newNode = malloc(sizeof(AVLNode));
    newNode->pair = createPairO(key, value);
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

AVLNode *rightRotateO(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxO(heightO(y->left), heightO(y->right)) + 1;
    x->height = maxO(heightO(x->left), heightO(x->right)) + 1;

    return x;
}

AVLNode *leftRotateO(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxO(heightO(x->left), heightO(x->right)) + 1;
    y->height = maxO(heightO(y->left), heightO(y->right)) + 1;

    return y;
}

AVLNode *insertNodeO(AVLNode *node, char *key, void *value) {
    if (node == NULL) {
        return createNodeO(key, value);
    }

    if (strcmp(node->pair->key, key) < 0) {
        node->right = insertNodeO(node->right, key, value);
    } else if (strcmp(node->pair->key, key) > 0) {
        node->left = insertNodeO(node->left, key, value);
    } else {
        return node;
    }

    node->height = 1 + maxO(heightO(node->left), heightO(node->right));

    int balance = getBalanceO(node);

    if (balance > 1 && strcmp(node->left->pair->key, key) > 0) {
        return rightRotateO(node);
    }

    if (balance < -1 && strcmp(node->right->pair->key, key) < 0) {
        return leftRotateO(node);
    }

    if (balance > 1 && strcmp(node->left->pair->key, key) < 0) {
        node->left = leftRotateO(node->left);
        return rightRotateO(node);
    }

    if (balance < -1 && strcmp(node->right->pair->key, key) > 0) {
        node->right = rightRotateO(node->right);
        return leftRotateO(node);
    }

    return node;
}

Pair *searchNodeO(AVLNode *node, char *key) {
    if (node == NULL || strcmp(node->pair->key, key) == 0) {
        return node != NULL ? node->pair : NULL;
    }

    if (strcmp(node->pair->key, key) < 0) {
        return searchNodeO(node->right, key);
    }

    return searchNodeO(node->left, key);
}

AVLNode *minValueNodeO(AVLNode *node) {
    AVLNode *current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

AVLNode *deleteNodeO(AVLNode *root, char *key) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(root->pair->key, key) < 0) {
        root->right = deleteNodeO(root->right, key);
    } else if (strcmp(root->pair->key, key) > 0) {
        root->left = deleteNodeO(root->left, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            AVLNode *temp = minValueNodeO(root->right);
            root->pair = temp->pair;
            root->right = deleteNodeO(root->right, temp->pair->key);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + maxO(heightO(root->left), heightO(root->right));

    int balance = getBalanceO(root);

    if (balance > 1 && getBalanceO(root->left) >= 0) {
        return rightRotateO(root);
    }

    if (balance > 1 && getBalanceO(root->left) < 0) {
        root->left = leftRotateO(root->left);
        return rightRotateO(root);
    }

    if (balance < -1 && getBalanceO(root->right) <= 0) {
        return leftRotateO(root);
    }

    if (balance < -1 && getBalanceO(root->right) > 0) {
        root->right = rightRotateO(root->right);
        return leftRotateO(root);
    }

    return root;
}

AVLTree *createMapO() {
    AVLTree *tree = malloc(sizeof(AVLTree));
    tree->root = NULL;
    return tree;
}

void insertMapO(AVLTree *tree, char *key, void *value) {
    tree->root = insertNodeO(tree->root, key, value);
}

void eraseMapO(AVLTree *tree, char *key) {
    tree->root = deleteNodeO(tree->root, key);
}

Pair *searchMapO(AVLTree *tree, char *key) {
    return searchNodeO(tree->root, key);
}

Pair *firstMapO(AVLTree *tree) {
    AVLNode *node = tree->root;
    while (node && node->left != NULL) {
        node = node->left;
    }
    if (node) {
        return node->pair;
    }
    return NULL;
}

Pair *nextMapO(AVLTree *tree) {
    static AVLNode *prev = NULL;
    if (tree == NULL) {
        prev = NULL;
        return NULL;
    }

    if (prev == NULL) {
        prev = minValueNodeO(tree->root);
        return prev ? prev->pair : NULL;
    }

    if (prev->right != NULL) {
        prev = minValueNodeO(prev->right);
        return prev ? prev->pair : NULL;
    }

    AVLNode *successor = NULL;
    AVLNode *current = tree->root;
    while (current != NULL) {
        if (strcmp(prev->pair->key, current->pair->key) < 0) {
            successor = current;
            current = current->left;
        } else if (strcmp(prev->pair->key, current->pair->key) > 0) {
            current = current->right;
        } else {
            break;
        }
    }

    prev = successor;
    return prev ? prev->pair : NULL;
}
