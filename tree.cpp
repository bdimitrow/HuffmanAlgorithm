#include "tree.h"

HuffmanTree::HuffmanTree() {
    root = nullptr;
}

HuffmanTree::HuffmanTree(const char *str) {
    std::priority_queue<HuffmanTreeNode *, std::vector<HuffmanTreeNode *>, compareHuffmanTree> forest;

    int occurs[256] = {0};
    while (*str) {
        occurs[(char) *str++]++;
    }

    /**
     * Creating nodes for every symbol with a non-zero occurrence and adding it to the queue.
     */
    for (int i = 0; i < 256; ++i) {
        if (occurs[i] != 0) {
            HuffmanTreeNode *toAddNode = new HuffmanTree::HuffmanTreeNode((char) i, occurs[i]);
            forest.push(toAddNode);
        }
    }

    while (forest.size() > 1) {
        HuffmanTreeNode *left = forest.top();
        forest.pop();
        HuffmanTreeNode *right = forest.top();
        forest.pop();
        HuffmanTreeNode *toPush = new HuffmanTreeNode(left, right);
        forest.push(toPush);
    }
    root = forest.top();
}

HuffmanTree::HuffmanTree(std::vector<std::pair<char, std::string>> &codePairs) {
    HuffmanTreeNode *tree = new HuffmanTreeNode('`', 1);
    HuffmanTreeNode *current = tree;
    for (auto &codePair : codePairs) {
        for (int j = 0; j < codePair.second.length(); ++j) {
            if (codePair.second.at(j) == '0') {
                if (current->left == nullptr) {
                    current->left = new HuffmanTreeNode(codePair.first, 0);
                    current = current->left;
                } else {
                    current = current->left;
                }
            } else { // codePair.second.at(j) == '1'
                if (current->right == nullptr) {
                    current->right = new HuffmanTreeNode(codePair.first, 1);
                    current = current->right;
                } else {
                    current = current->right;
                }
            }
        }
        current = tree;
    }
    root = tree;
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

void HuffmanTree::makePairs(std::vector<std::pair<char, std::string>> &vec) {
    makePairs(root, "", vec);
}

void HuffmanTree::makePairs(HuffmanTree::HuffmanTreeNode *current, std::string str,
                            std::vector<std::pair<char, std::string>> &vec) {
    if (current->left) {
        makePairs(current->left, str + '0', vec);
    }
    if (current->right) {
        makePairs(current->right, str + '1', vec);
    }
    if (current != nullptr && isLeaf(current)) {
        vec.push_back(std::make_pair(current->symbol, str));
    }
}

std::string HuffmanTree::decode_string(const std::string &binaryStr) {
    std::string result;
    HuffmanTreeNode *curr = root;
    for (const char &i : binaryStr) {
        if (i == '0') {
            curr = curr->left;
        } else { // i == '1'
            curr = curr->right;
        }
        // leaf node ? adding the symbol to the result string
        if (isLeaf(curr)) {
            result += curr->symbol;
            curr = root;
        }
    }

    return result;
}

HuffmanTree::HuffmanTreeNode::HuffmanTreeNode(char data, int occur) {
    symbol = data;
    occurrences = occur;
    left = right = nullptr;
}

HuffmanTree::HuffmanTreeNode::HuffmanTreeNode(HuffmanTree::HuffmanTreeNode *l, HuffmanTree::HuffmanTreeNode *r) {
    symbol = '`';  // rarely used symbol
    occurrences = l->occurrences + r->occurrences;
    left = l;
    right = r;
}
