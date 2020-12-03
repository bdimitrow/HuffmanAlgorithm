#include <iostream>
#include "tree.h"
#include "utils.h"
#include <cstring>


void printCode(HuffmanTree::HuffmanTreeNode *root, std::string str){
    if(root->left){
        printCode(root->left, str+'0');
    }
    if(root->right){
        printCode(root->right,str+'1');
    }
    if(root != nullptr && root->left == nullptr && root->right == nullptr) {
        std::cout << root->symbol << " : ";
        std::cout << str << std::endl;
    }

}

int main() {
    const char *str = "aaabbcddeeee";
    std::cout << " da\n";

    HuffmanTree tree;
    std::priority_queue<HuffmanTree::HuffmanTreeNode *, std::vector<HuffmanTree::HuffmanTreeNode *>, HuffmanTree::compareHuffmanTree> mht = createHuffmanForest(str);
    HuffmanTree *tree2 = new HuffmanTree(mht);
    int arr[] = {};
    HuffmanTree::HuffmanTreeNode *t = tree2->rootGetter();
    printCode(t, "");
    std::cout << " dada";
    return 0;
}