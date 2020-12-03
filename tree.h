//
// Created by bozhidar on 12/2/20.
//

#ifndef HUFFMANALGORITHM_TREE_H
#define HUFFMANALGORITHM_TREE_H

#include <iostream>
#include <queue>

struct HuffmanTree {
    char symbol;
    int occurrences;
    HuffmanTree *left, *right;

    HuffmanTree(char data, int occur) {
        symbol = data;
        occurrences = occur;
        left = right = nullptr;
    }

    HuffmanTree(HuffmanTree *l, HuffmanTree *r) {
        // TODO
        // symbol = ?;
        occurrences = l->occurrences + r->occurrences;
        left = l;
        right = r;
    }
};

struct compareHuffmanTrees {
    bool operator()(HuffmanTree *left, HuffmanTree *right) {
        return (left->occurrences > right->occurrences);
    }
};

std::priority_queue<HuffmanTree *, std::vector<HuffmanTree *>, compareHuffmanTrees> createHuffmanForest(const char *cstr) {
    // Here the tree will me sorted from minimum occurrences -> maximum
    std::priority_queue<HuffmanTree *, std::vector<HuffmanTree *>, compareHuffmanTrees> minimalHuffmanTrees;

    // Extracting the number of occurences of each symbol according to the ASCII.
    int occurs[256] = {0};
    while (*cstr) {
        occurs[(char) *cstr++]++;
    }

    // Pushing all symbols in priority queue.
    for (int i = 0; i < 256; ++i) {
        if (occurs[i] != 0) {
            HuffmanTree *toAdd = new HuffmanTree((char) i, occurs[i]);
            minimalHuffmanTrees.push(toAdd);
        }
    }

    return minimalHuffmanTrees;
}

HuffmanTree *createHuffmanTree(std::priority_queue<HuffmanTree> forest) {
    
}




#endif //HUFFMANALGORITHM_TREE_H
