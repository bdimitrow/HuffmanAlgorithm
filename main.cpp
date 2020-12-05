#include <iostream>
#include "tree.h"
#include "utils.h"
#include <cstring>
#include <fstream>
#include <sstream>

int main() {
    auto *t = new HuffmanTree(readFile().c_str());
//    t->printCode();

    std::vector<std::pair<char, std::string>> pairs;
    t->makePairs(pairs);
    std::string str = readFile();
    std::cout <<"str: " << str << std::endl;

    saveBinaryStringToFile(convertStringToBinary(str,pairs));

//    int i =0;
//    while (str[i]) {
//        for (auto el : pairs) {
//            if (str[i] == el.first) {
//                output += el.second;
//            }
//        }
//        ++i;
//    }
//
//    std::cout << "output: " << output << std::endl;


//    std::ofstream out;
//    out.open("testString.txt");
//    if (out.is_open()) {
//        out << "dada nee de s !, sd k\n";
//        out.close();
//    } else { std::cout << "unable to open\n"; }

//    HuffmanTree *tree;
//    std::string str;
//    std::ifstream in;
//    in.open("testString.txt");
//    if (in.is_open()) {
//            std::ostringstream ss;
//            ss << in.rdbuf();
//            str = ss.str();
//        in.close();
//    }
////    std::cout << str << std::endl;
//        tree = new HuffmanTree(str.c_str());
//    tree->printCode();

    //    const char *str = "aa a bbc dd ee ee";
//    std::cout << " da\n";
//
//
//    HuffmanTree *tree = new HuffmanTree(str);
////    std::priority_queue<HuffmanTree::HuffmanTreeNode *, std::vector<HuffmanTree::HuffmanTreeNode *>, HuffmanTree::compareHuffmanTree> mht = createHuffmanForest(str);
//////    createHuffmanForest(str);
////
////    HuffmanTree *tree2 = new HuffmanTree(mht);
//
////    HuffmanTree::HuffmanTreeNode *t = tree2->getRoot();
//////    printCode(t, "");
////    std::vector<std::pair<char,std::string>> pairVector;
////
////    makePairs(t,"", pairVector);
////    for(auto i : pairVector){
////        std::cout << i.first << " : " << i.second << std::endl;
////    }
//    tree->printCode();
    std::cout << " dada";
    return 0;
}