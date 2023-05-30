#ifndef MAPAORDENADO_H
#define MAPAORDENADO_H

typedef struct AVLNode AVLNode;
typedef struct AVLTree AVLTree;

typedef struct Pair {
    char *key;
    void *value;
} Pair;

AVLTree *createMapO();
void insertMapO(AVLTree *tree, char *key, void *value);
void eraseMapO(AVLTree *tree, char *key);
Pair *searchMapO(AVLTree *tree, char *key);
Pair *firstMapO(AVLTree *tree);
Pair *nextMapO(AVLTree *tree);

#endif
