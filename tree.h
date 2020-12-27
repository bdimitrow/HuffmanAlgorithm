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
         * For the symbol of the parent I choose a rarely used symbol '`'.
         */
        HuffmanTreeNode(HuffmanTreeNode *, HuffmanTreeNode *);

        /**
         * Operator < that compares two HuffmanTreeNodes by the occurrences field.
         * @param other
         * @return this->occurrences < other.occurrences
         */
        inline bool operator<(const HuffmanTreeNode &other) const { return this->occurrences < other.occurrences; }
    };

    HuffmanTreeNode *root{};

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

    /**
     * Constructor for HuffmanTree using a char array. Used when compressing a file. The source file is extracted into
     * a char array and the amount of times that each symbol appears is known. Afterwards a Huffman forest is created
     * and stored into a priority queue. The two trees with the smallest amount of occurrences are combined into one tree.
     * When the priority queue has just one element, that element is pointer to the root of the tree.
     */
    explicit HuffmanTree(const char *);

    /**
     * Constructor for HuffmanTree using a vector of pairs made of char and string. Used when decompressing a file. In
     * a compressed file the Huffman tree is saved as a string that is converted to a vector of pairs of char and string
     * corresponding to that character. The tree is rebuild with this vector. If the string symbol is 0 a left child is
     * created whether there is no one. A similar process happens when the string symbol is 1. However the child is the right one.
     */
    explicit HuffmanTree(std::vector<std::pair<char, std::string>> &);

    /**
     * A copy constructor.
     */
    HuffmanTree(const HuffmanTree &);

    /**
     * An operator =. That copies the 'other' tree to 'this' tree.
     */
    HuffmanTree &operator=(const HuffmanTree &);

    /**
     * A destructor.
     */
    ~HuffmanTree();

    /**
     * @fn inline bool isLeaf(HuffmanTreeNode *node)
     * Checks whether a node is a leaf(it has no children).
     * @param HuffmanTreeNode *node
     * @return bool
     */
    inline bool isLeaf(HuffmanTreeNode *node) { return node->left == nullptr && node->right == nullptr; }

    /**
     * @fn void makePairs(std::vector<std::pair<char, std::string>> &)
     * Uses the private function makePairs to create vector of pairs for the public.
     */
    void makePairs(std::vector<std::pair<char, std::string>> &);

    /**
     * @fn std::string decode_string(const std::string &)
     * @param std::string binaryStr
     * The function takes the binary string and traverse through the tree. When the string symbol is '0' the traversal
     * goes to the left child and when it is '1' the traversal goes to the right child. Reaching a leaf node, the node's symbol
     * is added to the resulting string. When the binaryStr is exhausted the resulting string is returned.
     * @return std::string result
     */
    // taking binary string and converting it to normal according to the tree;
    std::string decode_string(const std::string &);

private:
    /**
     * @fn void clear(NuffmanTreeNode *node)
     * Recursively deleting a node and its subtrees.
     */
    void clear(HuffmanTreeNode *);

    /**
     * @fn void copy(const HuffmanTree &)
     * Using the copyHuffmanTreeNode to make a copy of the tree.
     */
    void copy(const HuffmanTree &);

    /**
     * @fn HuffmanTreeNode *copyHuffmanTreeNode(HuffmanTreeNode *)
     * Recursively coping a node and its subtrees.
     * @return A copy of the node and its subtrees.
     */
    HuffmanTreeNode *copyHuffmanTreeNode(HuffmanTreeNode *);

    /**
     * @fn void makePairs(HuffmanTreeNode *, std::string, std::vector<std::pair<char, std::string>> &)
     * Called by the public one. The function iterates through the tree until it reaches a leaf node. When going to the left
     * node a '0' is added to the string and when going to the right child a '1' is added. When a leaf is reached the currently generated
     * string and the leaf's symbol are added to the vector of pairs.
     */
    void makePairs(HuffmanTreeNode *, std::string, std::vector<std::pair<char, std::string>> &);
};

#endif //HUFFMANALGORITHM_TREE_H
