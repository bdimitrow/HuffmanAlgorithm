//
// Created by bozhidar on 12/2/20.
//

#ifndef HUFFMANALGORITHM_TREE_H
#define HUFFMANALGORITHM_TREE_H


struct HuffmanTree {
    char symbol;
    int occurrences;
    HuffmanTree *left, *right;

    HuffmanTree(int occurrences,)
};

struct compareHuffmanTrees {
    bool operator()(HuffmanTree *left, HuffmanTree *right) {
        return (left->occurrences > right->occurrences);
    }
};

#endif //HUFFMANALGORITHM_TREE_H
