//
// Created by bozhidar on 12/3/20.
//

#ifndef HUFFMANALGORITHM_UTILS_H
#define HUFFMANALGORITHM_UTILS_H

#include <iostream>
#include "tree.h"

//std::priority_queue<HuffmanTree::HuffmanTreeNode *, std::vector<HuffmanTree::HuffmanTreeNode *>, HuffmanTree::compareHuffmanTree>
//createHuffmanForest(const char *cstr) {
//    // Here the tree will me sorted from minimum occurrences -> maximum
//    std::priority_queue<HuffmanTree::HuffmanTreeNode *, std::vector<HuffmanTree::HuffmanTreeNode *>, HuffmanTree::compareHuffmanTree> minimalQueue;
//
//    // Extracting the number of occurences of each symbol according to the ASCII.
//    int occurs[256] = {0};
//    while (*cstr) {
//        occurs[(char) *cstr++]++;
//    }
//
//    // Pushing all symbols in priority queue.
//    for (int i = 0; i < 256; ++i) {
//        if (occurs[i] != 0) {
//            HuffmanTree::HuffmanTreeNode *toAddNode = new HuffmanTree::HuffmanTreeNode((char) i, occurs[i]);
//            minimalQueue.push(toAddNode);
//        }
//    }
//
//    return minimalQueue;
//}

//void printCode(HuffmanTree::HuffmanTreeNode *root, std::string str) {
//    if (root->left) {
//        printCode(root->left, str + '0');
//    }
//    if (root->right) {
//        printCode(root->right, str + '1');
//    }
//    if (root != nullptr && root->left == nullptr && root->right == nullptr) {
//        std::cout << root->symbol << " : ";
//        std::cout << str << std::endl;
//    }
//}
//
//void makePairs(HuffmanTree::HuffmanTreeNode *root, std::string str, std::vector<std::pair<char, std::string>> &vec) {
//    if (root->left) {
//        makePairs(root->left, str + '0', vec);
//    }
//    if (root->right) {
//        makePairs(root->right, str + '1', vec);
//    }
//    if (root != nullptr && root->left == nullptr && root->right == nullptr) {
//        vec.push_back(std::make_pair(root->symbol, str));
//    }
//}


#endif //HUFFMANALGORITHM_UTILS_H
