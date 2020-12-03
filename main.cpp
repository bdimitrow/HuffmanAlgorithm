#include <iostream>
#include "tree.h"
#include <cstring>


int main() {
    const char *str = "aaabbcddeeee";
    std::priority_queue<HuffmanTree*, std::vector<HuffmanTree *>, compareHuffmanTrees> mht = createHuffmanForest(str);
    std::cout << " da";

    return 0;
}