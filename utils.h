//
// Created by bozhidar on 12/3/20.
//

#ifndef HUFFMANALGORITHM_UTILS_H
#define HUFFMANALGORITHM_UTILS_H

#include <iostream>
#include "tree.h"

std::priority_queue<HuffmanTree::HuffmanTreeNode *, std::vector<HuffmanTree::HuffmanTreeNode *>, HuffmanTree::compareHuffmanTree>
createHuffmanForest(const char *cstr) {
    // Here the tree will me sorted from minimum occurrences -> maximum
    std::priority_queue<HuffmanTree::HuffmanTreeNode *, std::vector<HuffmanTree::HuffmanTreeNode *>, HuffmanTree::compareHuffmanTree> minimalHuffmanTrees;

    // Extracting the number of occurences of each symbol according to the ASCII.
    int occurs[256] = {0};
    while (*cstr) {
        occurs[(char) *cstr++]++;
    }

    // Pushing all symbols in priority queue.
    for (int i = 0; i < 256; ++i) {
        if (occurs[i] != 0) {
            HuffmanTree::HuffmanTreeNode *toAddNode = new HuffmanTree::HuffmanTreeNode((char) i, occurs[i]);
            minimalHuffmanTrees.push(toAddNode);
        }
    }

    return minimalHuffmanTrees;
}

#endif //HUFFMANALGORITHM_UTILS_H
