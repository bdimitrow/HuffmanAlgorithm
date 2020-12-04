#include <iostream>
#include "tree.h"
#include "utils.h"
#include <cstring>


int main() {
    const char *str = "aa a bbc dd ee ee";
    std::cout << " da\n";

    HuffmanTree *tree = new HuffmanTree();
    std::priority_queue<HuffmanTree::HuffmanTreeNode *, std::vector<HuffmanTree::HuffmanTreeNode *>, HuffmanTree::compareHuffmanTree> mht = createHuffmanForest(str);
//    createHuffmanForest(str);

    HuffmanTree *tree2 = new HuffmanTree(mht);

//    HuffmanTree::HuffmanTreeNode *t = tree2->getRoot();
////    printCode(t, "");
//    std::vector<std::pair<char,std::string>> pairVector;
//
//    makePairs(t,"", pairVector);
//    for(auto i : pairVector){
//        std::cout << i.first << " : " << i.second << std::endl;
//    }
    std::cout << " dada";
    return 0;
}