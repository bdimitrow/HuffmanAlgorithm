//
// Created by bozhidar on 12/2/20.
//

#ifndef HUFFMANALGORITHM_TREE_H
#define HUFFMANALGORITHM_TREE_H

#include <iostream>
#include <queue>

/*! \class HuffmanTree
 * \brief A Huffman tree class.
 *
 * This class is used to build a Huffman tree from an occurrence table(when compressing) and from string(when decompressing).
 */

/**
 * @param root is a pointer of type HuffmanTreeNode
 */
class HuffmanTree {
private:
    /**
     * \struct HuffmanTreeNode
     * \brief representing a node in the Huffman tree. Every node contains @param char symbol, @param int occurrences (of the char)
     * @param HuffmanTreeNode *left, *right.
     */
    struct HuffmanTreeNode {
        char symbol;
        int occurrences;
        HuffmanTreeNode *left, *right;

        /**
         * A constructor that creates a node from a char and an int and the children(*left and *right) are nullpointers.
         */
        HuffmanTreeNode(char, int);

        /**
         * A constructor that takes two nodes and creates their parent(where the occurrences field equals the sum of the occurrences of the children).
         */
        HuffmanTreeNode(HuffmanTreeNode *, HuffmanTreeNode *);

        /**
         * Operator < that compares two HuffmanTreeNodes by the occurrences field.
         * @param other
         * @return this->occurrences < other.occurrences
         */
        inline bool operator<(const HuffmanTreeNode &other) const { return this->occurrences < other.occurrences; }
    };

    HuffmanTreeNode *root;

    /**
     * А compare function used as a sorting predicate in the priority queue
     */
    struct compareHuffmanTree {
        bool operator()(HuffmanTreeNode *left, HuffmanTreeNode *right) {
            return left->occurrences > right->occurrences;
        }
    };

public:
    /**
     * A default constructor.
     */
    HuffmanTree();

    // building a huffman tree from the source file;
    /**
     * Constructor for HuffmanTree using a char array. Used when compressing a file. The source file is extracted into
     * a char array and the amount of times that each symbol appears is known. Afterwards a Huffman forest is created
     * and stored into a priority queue. The two trees with the smallest amount of occurrences are combined into one tree.
     * When the priority queue has just one element, that element is pointer to the root of the tree.
     */
    explicit HuffmanTree(const char *);

    /**
     * Constructor for HuffmanTree using a vector of pairs made of char and string.
     */
    explicit HuffmanTree(std::vector<std::pair<char, std::string>> &);

    HuffmanTree(const HuffmanTree &);

    HuffmanTree &operator=(const HuffmanTree &);

    ~HuffmanTree();

    inline bool isLeaf(HuffmanTreeNode *curr) { return curr->left == nullptr && curr->right == nullptr; }

    void makePairs(std::vector<std::pair<char, std::string>> &);

    // taking binary string and converting it to normal according to the tree;
    std::string decode_string(std::string s);

private:
    void clear(HuffmanTreeNode *);

    void copy(const HuffmanTree &);

    HuffmanTreeNode *copyHuffmanTreeNode(HuffmanTreeNode *);

    void makePairs(HuffmanTreeNode *, std::string, std::vector<std::pair<char, std::string>> &);
};


#endif //HUFFMANALGORITHM_TREE_H
