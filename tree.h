//
// Created by bozhidar on 12/2/20.
//

#ifndef HUFFMANALGORITHM_TREE_H
#define HUFFMANALGORITHM_TREE_H

#include <iostream>
#include <queue>


class HuffmanTree {
private:
    struct HuffmanTreeNode {
        char symbol;
        int occurrences;
        HuffmanTreeNode *left, *right;

        HuffmanTreeNode(char data, int occur) {
            symbol = data;
            occurrences = occur;
            left = right = nullptr;
        }

        HuffmanTreeNode(HuffmanTreeNode *l, HuffmanTreeNode *r) {
            symbol = '`';  // rarely used symbol
            occurrences = l->occurrences + r->occurrences;
            left = l;
            right = r;
        }

        bool operator<(const HuffmanTreeNode &other) const {
            return this->occurrences < other.occurrences;
        }
    };

private:
    HuffmanTreeNode *root;


public:
    struct compareHuffmanTree {
        bool operator()(HuffmanTreeNode *left, HuffmanTreeNode *right) {
            return left->occurrences > right->occurrences;
        }
    };



public:
    HuffmanTree();

    HuffmanTree(char, int);

    HuffmanTree(HuffmanTree *, HuffmanTree *);

    explicit HuffmanTree(std::priority_queue<HuffmanTreeNode *, std::vector<HuffmanTreeNode *>, compareHuffmanTree>);

    HuffmanTree(const HuffmanTree &);

    HuffmanTree &operator=(const HuffmanTree &);

    ~HuffmanTree();

    inline HuffmanTreeNode *getRoot() { return root; }

    friend std::priority_queue<HuffmanTree::HuffmanTreeNode *, std::vector<HuffmanTree::HuffmanTreeNode *>, HuffmanTree::compareHuffmanTree>
    createHuffmanForest(const char *cstr);

private:
    void clear(HuffmanTreeNode *);

    void copy(const HuffmanTree &);

    HuffmanTreeNode *copyHuffmanTreeNode(HuffmanTreeNode *);

};


#endif //HUFFMANALGORITHM_TREE_H
