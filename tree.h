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

    HuffmanTreeNode *root;

    // used as a sorting function in the prority queue
    struct compareHuffmanTree {
        bool operator()(HuffmanTreeNode *left, HuffmanTreeNode *right) {
            return left->occurrences > right->occurrences;
        }
    };


public:
    HuffmanTree();

    HuffmanTree(char, int);

    // building a huffman tree from the source file;
    HuffmanTree(const char *str);

    // @TODO to rebuilt the tree from the compressed file??
    explicit HuffmanTree(std::vector<std::pair<char, std::string>> &);

    HuffmanTree(const HuffmanTree &);

    HuffmanTree &operator=(const HuffmanTree &);

    ~HuffmanTree();

    ////////////////////////////////////////////////

    inline HuffmanTreeNode *getRoot() { return root; }

    void printCode();

    void makePairs(std::vector<std::pair<char, std::string>> &);

    // taking binary string and converting it to normal according to the tree;
    std::string decode_file(std::string s);

private:
    void clear(HuffmanTreeNode *);

    void copy(const HuffmanTree &);

    HuffmanTreeNode *copyHuffmanTreeNode(HuffmanTreeNode *);

    void printCode(HuffmanTreeNode *, std::string);

    void makePairs(HuffmanTreeNode *, std::string, std::vector<std::pair<char, std::string>> &);
};


#endif //HUFFMANALGORITHM_TREE_H
