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
            // TODO
            symbol = '@';
            occurrences = l->occurrences + r->occurrences;
            left = l;
            right = r;
        }

        bool operator<(const HuffmanTreeNode &other) {
            return this->occurrences < other.occurrences;
        }
    };

    struct compareHuffmanTree {
        bool operator()(HuffmanTree const& left, HuffmanTree const& right) {
            return left.root->occurrences > right.root->occurrences;
        }
    };

    HuffmanTreeNode *root;


public:
    HuffmanTree();

    HuffmanTree(std::priority_queue<HuffmanTreeNode *>);

    HuffmanTree(const HuffmanTree &);

    HuffmanTree &operator=(const HuffmanTree &);

    ~HuffmanTree();

    std::priority_queue<HuffmanTree *, std::vector<HuffmanTree *>, compareHuffmanTree>createHuffmanForest(const char *cstr) {
        // Here the tree will me sorted from minimum occurrences -> maximum
        std::priority_queue<HuffmanTree *, std::vector<HuffmanTree *>, compareHuffmanTree> minimalHuffmanTrees;

        // Extracting the number of occurences of each symbol according to the ASCII.
        int occurs[256] = {0};
        while (*cstr) {
            occurs[(char) *cstr++]++;
        }

        // Pushing all symbols in priority queue.
        for (int i = 0; i < 256; ++i) {
            if (occurs[i] != 0) {
                HuffmanTreeNode *toAddNode = new HuffmanTreeNode((char) i, occurs[i]);
                HuffmanTree *add = new HuffmanTree();
                add->root = toAddNode;
                minimalHuffmanTrees.push(add);
            }
        }

        return minimalHuffmanTrees;
    }

private:
    void clear(HuffmanTreeNode *);

    void copy(const HuffmanTree &);

    HuffmanTreeNode *copyHuffmanTreeNode(HuffmanTreeNode *);

};


#endif //HUFFMANALGORITHM_TREE_H
