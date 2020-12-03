//
// Created by bozhidar on 12/2/20.
//
//

#include "tree.h"

HuffmanTree::HuffmanTree() {
    root = nullptr;
}

HuffmanTree::HuffmanTree(char data, int occur) {
    root = new HuffmanTreeNode(data, occur);
}

HuffmanTree::HuffmanTree(HuffmanTree *l, HuffmanTree *r) {
    HuffmanTreeNode *add = new HuffmanTreeNode(l->root, r->root);
    root = add;
}


HuffmanTree::HuffmanTree(std::priority_queue<HuffmanTreeNode *, std::vector<HuffmanTreeNode *>, compareHuffmanTree> forest) {
    while (forest.size() > 1) {
        HuffmanTreeNode *left = forest.top();
        forest.pop();
        HuffmanTreeNode *right = forest.top();
        forest.pop();
        HuffmanTreeNode *toPush = new HuffmanTreeNode(left,right);
        forest.push(toPush);
    }
    root = forest.top();
}

HuffmanTree::HuffmanTree(const HuffmanTree &other) {
    copy(other);
}

HuffmanTree &HuffmanTree::operator=(const HuffmanTree &other) {
    if (this != &other) {
        clear(this->root);
        copy(other);
    }
    return *this;
}

HuffmanTree::~HuffmanTree() {
    clear(root);
}

void HuffmanTree::clear(HuffmanTreeNode *current) {
    if (current == nullptr) {
        return;
    }
    clear(current->left);
    clear(current->right);

    delete current;
}

void HuffmanTree::copy(const HuffmanTree &other) {
    root = copyHuffmanTreeNode(other.root);
}

HuffmanTree::HuffmanTreeNode *HuffmanTree::copyHuffmanTreeNode(HuffmanTree::HuffmanTreeNode *current) {
    if (current == nullptr) {
        return nullptr;
    }

    HuffmanTreeNode *copied = new HuffmanTreeNode(current->symbol, current->occurrences);
    copied->left = copyHuffmanTreeNode(current->left);
    copied->right = copyHuffmanTreeNode(current->right);

    return copied;
}



