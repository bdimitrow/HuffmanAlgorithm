//
// Created by bozhidar on 12/2/20.
//
//

#include "tree.h"

HuffmanTree::HuffmanTree() {
    root = nullptr;
}

HuffmanTree::HuffmanTree(char data, int occur) {
    root = new HuffmanTreeNode(data, occur);
}


HuffmanTree::HuffmanTree(const char *str) {
    std::priority_queue<HuffmanTreeNode *, std::vector<HuffmanTreeNode *>, compareHuffmanTree> forest;

    int occurs[256] = {0};
    while (*str) {
        occurs[(char) *str++]++;
    }

    // Pushing all symbols in priority queue.
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
    for (int i = 0; i < codePairs.size(); ++i) {
        for (int j = 0; j < codePairs.at(i).second.length(); ++j) {
            if (codePairs.at(i).second.at(j) == '0') {
                if (current->left == nullptr) {
                    current->left = new HuffmanTreeNode(codePairs.at(i).first, 0);
                    current = current->left;
                } else {
                    current = current->left;
                }
            } else {
                if (current->right == nullptr) {
                    current->right = new HuffmanTreeNode(codePairs.at(i).first, 1);
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

void HuffmanTree::printCode() {
    printCode(root, "");
}

void HuffmanTree::printCode(HuffmanTree::HuffmanTreeNode *current, std::string str) {
    if (current->left) {
        printCode(current->left, str + '0');
    }
    if (current->right) {
        printCode(current->right, str + '1');
    }
    if (current != nullptr && current->left == nullptr && current->right == nullptr) {
        std::cout << current->symbol << " : ";
        std::cout << str << std::endl;
    }
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
    if (current != nullptr && current->left == nullptr && current->right == nullptr) {
        vec.push_back(std::make_pair(current->symbol, str));
    }
}

std::string HuffmanTree::decode_string(std::string s) {
    std::string result;
    HuffmanTreeNode *curr = root;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0') {
            curr = curr->left;
        } else {
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
