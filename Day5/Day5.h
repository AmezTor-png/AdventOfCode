#ifndef DAY5_H
#define DAY5_H

#include <algorithm>

struct IntervalNode {
    long long low, high;
    long long max;
    IntervalNode* left;
    IntervalNode* right;

    IntervalNode(long long l, long long h) : low(l), high(h), max(h), left(nullptr), right(nullptr) {}
};

// Insertamos un rango en el árbol
IntervalNode* insert(IntervalNode* root, long long l, long long h) {
    if (!root) return new IntervalNode(l, h);
    if (l < root->low) {
        root->left = insert(root->left, l, h);
    } else {
        root->right = insert(root->right, l, h);
    }
    root->max = std::max(root->max, h);
    return root;
}

// Buscar si un ID está en algún rango
bool contains(IntervalNode* root, long long id) {
    if (!root) return false;
    if (id >= root->low && id <= root->high) return true;
    if (root->left && root->left->max >= id) return contains(root->left, id);
    return contains(root->right, id);
}

#endif