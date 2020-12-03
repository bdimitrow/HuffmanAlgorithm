#include <iostream>
#include "tree.h"
#include "utils.h"
#include <cstring>


int main() {
    const char *str = "aaabbcddeeee";
    std::cout << " da\n";

    std::priority_queue<HuffmanTree::HuffmanTreeNode *, std::vector<HuffmanTree::HuffmanTreeNode *>, HuffmanTree::compareHuffmanTree> mht = createHuffmanForest(str);
    HuffmanTree *tree2 = new HuffmanTree(mht);

    HuffmanTree::HuffmanTreeNode *t = tree2->getRoot();
//    printCode(t, "");
    std::vector<std::pair<char,std::string>> pairVector;

    makePairs(t,"", pairVector);
    for(auto i : pairVector){
        std::cout << i.first << " : " << i.second << std::endl;
    }
    std::cout << " dada";
    return 0;
}